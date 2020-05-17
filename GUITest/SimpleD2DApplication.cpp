#include "SimpleD2DApplication.h"	

SimpleD2DApp::SimpleD2DApp() : 
	m_hwnd(NULL),
    m_pD2DFactory(NULL),
    m_pWICFactory(NULL),
    m_pDWriteFactory(NULL),
	m_pRenderTarget(NULL),
	m_pTextFormat(NULL),
	m_pPathGeometry(NULL),
	m_pLinearGradientBrush(NULL),
	m_pBlackBrush(NULL),
	m_pGridPatternBitmapBrush(NULL),
	m_pBitmap(NULL),
	m_pAnotherBitmap(NULL) {}

SimpleD2DApp::~SimpleD2DApp() {
	SafeRelease(&m_pD2DFactory);
	SafeRelease(&m_pWICFactory);
    SafeRelease(&m_pDWriteFactory);
	SafeRelease(&m_pRenderTarget);
	SafeRelease(&m_pTextFormat);
	SafeRelease(&m_pPathGeometry);
	SafeRelease(&m_pLinearGradientBrush);
	SafeRelease(&m_pBlackBrush);
	SafeRelease(&m_pGridPatternBitmapBrush);
	SafeRelease(&m_pBitmap);
	SafeRelease(&m_pAnotherBitmap);
}

HRESULT SimpleD2DApp::Initialize() {
	HRESULT hr;
	//initialize device-dependent resources,such as 
	//the Direct2D factory.
	hr = CreateDeviceIndependentResource();
	if (SUCCEEDED(hr)) {
		WNDCLASSEX wcex = { sizeof(WNDCLASSEX) };
		wcex.style = CS_HREDRAW | CS_VREDRAW;
		wcex.lpfnWndProc = SimpleD2DApp::WndProc;
		wcex.cbClsExtra = 0;
		wcex.cbWndExtra = sizeof(LONG_PTR);
		wcex.hInstance = HINST_THISCOMPONENT;
		wcex.hbrBackground = NULL;
		wcex.lpszMenuName = NULL;
		wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
		wcex.lpszClassName = L"SimpleD2DApp";

		RegisterClassEx(&wcex);
		
		//create the application window.
		UINT dpi;
		//get system dpi
		dpi = GetDpiForSystem();
		m_hwnd = CreateWindow(L"SimpleD2DApp",
			L"Direct2D Demo Application",
			WS_OVERLAPPEDWINDOW,
			CW_USEDEFAULT,
			CW_USEDEFAULT,
			static_cast<UINT>(ceil(640.f * dpi / 96.f)),
			static_cast<UINT>(ceil(480.f * dpi / 96.f)),
			NULL,
			NULL,
			HINST_THISCOMPONENT,
			this
		);
		hr = m_hwnd ? S_OK : E_FAIL;
		if (SUCCEEDED(hr)) {
			ShowWindow(m_hwnd, SW_SHOWNORMAL);
			UpdateWindow(m_hwnd);
		}
	}
	return hr;
}

void SimpleD2DApp::RunMessageLoop() {
	MSG msg;
	while (GetMessage(&msg, NULL, 0, 0)) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
}

HRESULT SimpleD2DApp::CreateDeviceIndependentResource() {
	static const WCHAR msc_fontName[] = L"Consolas";
	static const FLOAT msc_fontSize = 50;
	HRESULT hr;
	ID2D1GeometrySink* pSink = NULL;

	hr = D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &m_pD2DFactory);
	if (SUCCEEDED(hr)) {
		//Create WIC factory
		hr = CoCreateInstance(CLSID_WICImagingFactory, NULL,
			CLSCTX_INPROC_SERVER, IID_IWICImagingFactory,
			reinterpret_cast<void**>(&m_pWICFactory));
	}
	if (SUCCEEDED(hr)) {
        // Create a DirectWrite factory.
        hr = DWriteCreateFactory(
            DWRITE_FACTORY_TYPE_SHARED,
            __uuidof(m_pDWriteFactory),
            reinterpret_cast<IUnknown **>(&m_pDWriteFactory)
            );
	}
	if (SUCCEEDED(hr)) {
		//Create a DirectWrite text format object
        hr = m_pDWriteFactory->CreateTextFormat(
            msc_fontName,
            NULL,
			DWRITE_FONT_WEIGHT_NORMAL,
			DWRITE_FONT_STYLE_NORMAL,
			DWRITE_FONT_STRETCH_NORMAL,
			msc_fontSize, L"", &m_pTextFormat);
	}
	if (SUCCEEDED(hr)) {
		m_pTextFormat->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_CENTER);
		m_pTextFormat->SetParagraphAlignment(DWRITE_PARAGRAPH_ALIGNMENT_CENTER);
		//create a path geometry
		hr = m_pD2DFactory->CreatePathGeometry(&m_pPathGeometry);
	}
	if (SUCCEEDED(hr)) {
		//use the geometry sink to write to the path geometry
		hr = m_pPathGeometry->Open(&pSink);
	}
	if (SUCCEEDED(hr)) {
		pSink->SetFillMode(D2D1_FILL_MODE_ALTERNATE);

		pSink->BeginFigure(D2D1::Point2F(0, 0),
			D2D1_FIGURE_BEGIN_FILLED);
		pSink->AddLine(D2D1::Point2F(200, 0));

		pSink->AddBezier(D2D1::BezierSegment(
			D2D1::Point2F(150, 50),
			D2D1::Point2F(150, 150),
			D2D1::Point2F(200, 200)
		));

		pSink->AddLine(D2D1::Point2F(0, 200));

		pSink->AddBezier(D2D1::BezierSegment(
			D2D1::Point2F(50, 150),
			D2D1::Point2F(50, 50),
			D2D1::Point2F(0, 0)
		));

		pSink->EndFigure(D2D1_FIGURE_END_CLOSED);
		hr = pSink->Close();
	}
	SafeRelease(&pSink);
	return hr;
}

HRESULT SimpleD2DApp::CreateDeviceResource() {
	HRESULT hr = S_OK;

	if (!m_pRenderTarget) {
		RECT rc;
		GetClientRect(m_hwnd, &rc);
		D2D_SIZE_U size = D2D1::SizeU(
			rc.right - rc.left,
			rc.bottom - rc.top
		);

		//create a direct2d render target
		hr = m_pD2DFactory->CreateHwndRenderTarget(
			D2D1::RenderTargetProperties(),
			D2D1::HwndRenderTargetProperties(m_hwnd, size),
			&m_pRenderTarget
		);
		if (SUCCEEDED(hr)) {
			hr = m_pRenderTarget->CreateSolidColorBrush(
				D2D1::ColorF(D2D1::ColorF::Red),
				&m_pBlackBrush
			);
		}
		if (SUCCEEDED(hr)) {
			ID2D1GradientStopCollection* pGradientStops = NULL;
			//create a linear gradient
			static const D2D1_GRADIENT_STOP stops[] = {
				{0.f,{0.f,1.f,1.f,0.25f}},
				{1.f,{0.f,0.f,1.f,1.f}}
			};
			hr = m_pRenderTarget->CreateGradientStopCollection(
				stops,
				ARRAYSIZE(stops),
				&pGradientStops
			);
			if (SUCCEEDED(hr)) {
				hr = m_pRenderTarget->CreateLinearGradientBrush(
					D2D1::LinearGradientBrushProperties(
						D2D1::Point2F(100, 0),
						D2D1::Point2F(100, 200)),
					D2D1::BrushProperties(),
					pGradientStops,
					&m_pLinearGradientBrush
				);
				pGradientStops->Release();
			}
		}
		//create a bitmap from an application resource 
		hr = LoadResourceBitmap(
			m_pRenderTarget,
			m_pWICFactory,
			L"SampleImage",
			L"Image",
			100,
			0,
			&m_pBitmap
		);
		if (SUCCEEDED(hr)) {
			//create a bitmap by loading it from a file 
			hr = LoadBitmapFromFile(
				m_pRenderTarget,
				m_pWICFactory,
				L".\\sampleImage.jpg",
				100,
				0,
				&m_pAnotherBitmap
			);
		}
		if (SUCCEEDED(hr)) {
			hr = CreateGridPatternBrush(m_pRenderTarget, &m_pGridPatternBitmapBrush);
		}
	}
	return hr;
}

//creates a pattern brush
HRESULT SimpleD2DApp::CreateGridPatternBrush(
	ID2D1RenderTarget* pRenderTarget,
	ID2D1BitmapBrush** ppBitmapBrush
) {
	HRESULT hr = S_OK;

	//create a compatible render target
	ID2D1BitmapRenderTarget* pCompatibleRenderTarget = NULL;
	hr = pRenderTarget->CreateCompatibleRenderTarget(
		D2D1::SizeF(10.0f, 10.0f),
		&pCompatibleRenderTarget
	);
	if (SUCCEEDED(hr)) {
		//draw a pattern
		ID2D1SolidColorBrush* pGridBrush = NULL;
		hr = pCompatibleRenderTarget->CreateSolidColorBrush(
			D2D1::ColorF(D2D1::ColorF(0.93f, 0.94f, 0.96f, 1.0f)),
			&pGridBrush
		);
		if (SUCCEEDED(hr)) {
			pCompatibleRenderTarget->BeginDraw();
			pCompatibleRenderTarget->FillRectangle(D2D1::RectF(0.0f, 0.0f, 10.0f, 1.0f), pGridBrush);
			pCompatibleRenderTarget->FillRectangle(D2D1::RectF(0.0f, 0.1f, 1.0f, 10.0f), pGridBrush);
			pCompatibleRenderTarget->EndDraw();

			//retrieve the bitmap from the render target
			ID2D1Bitmap* pGridBitmap = NULL;
			hr = pCompatibleRenderTarget->GetBitmap(&pGridBitmap);
			if (SUCCEEDED(hr)) {
				//choose the tiling mode for the bitmap brush
				D2D1_BITMAP_BRUSH_PROPERTIES brushProperties = D2D1::BitmapBrushProperties(
					D2D1_EXTEND_MODE_WRAP, D2D1_EXTEND_MODE_WRAP
				);
				//create the bitmap brush
				hr = m_pRenderTarget->CreateBitmapBrush(pGridBitmap, brushProperties, ppBitmapBrush);
				pGridBitmap->Release();
			}
			pGridBrush->Release();
		}
		pCompatibleRenderTarget->Release();
	}
	return hr;
}

void SimpleD2DApp::DiscardDeviceResource() {
	SafeRelease(&m_pRenderTarget);
	SafeRelease(&m_pBitmap);
	SafeRelease(&m_pBlackBrush);
	SafeRelease(&m_pLinearGradientBrush);
	SafeRelease(&m_pAnotherBitmap);
	SafeRelease(&m_pGridPatternBitmapBrush);
}

HRESULT SimpleD2DApp::OnRender() {
	HRESULT hr;

	hr = CreateDeviceResource();

	if (SUCCEEDED(hr) && !(m_pRenderTarget->CheckWindowState() & D2D1_WINDOW_STATE_OCCLUDED)) {
		static const WCHAR sc_helloWorld[] = L"Pengman";
		//retrieve the size of the render target 
		D2D1_SIZE_F renderTargetSize = m_pRenderTarget->GetSize();
		m_pRenderTarget->BeginDraw();
		
		m_pRenderTarget->SetTransform(D2D1::Matrix3x2F::Identity());
		m_pRenderTarget->Clear(D2D1::ColorF(D2D1::ColorF::White));
		//paint a grid background
		m_pRenderTarget->FillRectangle(D2D1::RectF(0.0f, 0.0f, renderTargetSize.width,
			renderTargetSize.height), m_pGridPatternBitmapBrush);

		D2D1_SIZE_F size = m_pBitmap->GetSize();
		//draw a bitmap in the upper-left corner of the window 
		m_pRenderTarget->DrawBitmap(m_pBitmap, D2D1::RectF(0.0f, 0.0f, size.width, size.height));
		//draw a bitmap in at the lowere-right corner of the window 
		size = m_pAnotherBitmap->GetSize();
		m_pRenderTarget->DrawBitmap(m_pAnotherBitmap,
			D2D1::RectF(
				renderTargetSize.width - size.width,
				renderTargetSize.height - size.height,
				renderTargetSize.width,
				renderTargetSize.height)
			);

		//set the world transform to a 45 degree rotation at the center of the render target
		//and write pengman
		m_pRenderTarget->SetTransform(
			D2D1::Matrix3x2F::Rotation(
				45, D2D1::Point2F(
					renderTargetSize.width / 2,
					renderTargetSize.height / 2
				))
		);

		m_pRenderTarget->DrawText(sc_helloWorld,
            ARRAYSIZE(sc_helloWorld) - 1,
            m_pTextFormat,
			D2D1::RectF(0, 0, renderTargetSize.width, renderTargetSize.height),
			m_pBlackBrush);

		//reset back to the identity transform
		m_pRenderTarget->SetTransform(
			D2D1::Matrix3x2F::Translation(0, renderTargetSize.height - 200)
		);
		//fill the hour glass geometry with a gradient
		m_pRenderTarget->FillGeometry(m_pPathGeometry, m_pLinearGradientBrush);
		m_pRenderTarget->SetTransform(
			D2D1::Matrix3x2F::Translation(renderTargetSize.width - 200, 0)
		);
		//fill the hour glass geometry with a gradient
		m_pRenderTarget->FillGeometry(m_pPathGeometry, m_pLinearGradientBrush);

		hr = m_pRenderTarget->EndDraw();

		if (hr == D2DERR_RECREATE_TARGET)
		{
			hr = S_OK;
			DiscardDeviceResource();
		}
	}
	return hr;
}

void SimpleD2DApp::OnResize(
	UINT width,
	UINT height
) {
	if (m_pRenderTarget) {
		D2D1_SIZE_U size;
		size.width = width;
		size.height = height;
        m_pRenderTarget->Resize(size);
	}
}

LRESULT CALLBACK SimpleD2DApp::WndProc(
	HWND hwnd,
	UINT message,
	WPARAM wParam,
	LPARAM lParam
) {
	LRESULT result = 0;
	if (message == WM_CREATE) {
		LPCREATESTRUCT pcs = (LPCREATESTRUCT)lParam;
		SimpleD2DApp* pSimpleD2DApp = (SimpleD2DApp*)pcs->lpCreateParams;
		::SetWindowLongPtrW(
			hwnd, GWLP_USERDATA, PtrToLong(pSimpleD2DApp));
		result = 1;
	}
	else {
		SimpleD2DApp* pSimpleD2DApp = reinterpret_cast<SimpleD2DApp*>(static_cast<LONG_PTR>(
			::GetWindowLongPtrW(
				hwnd, GWLP_USERDATA
			)));
		bool wasHandled = false;

		if (pSimpleD2DApp) {
			switch (message) {
			case WM_SIZE:
			{
				UINT width = LOWORD(lParam);
				UINT height = HIWORD(lParam);
				pSimpleD2DApp->OnResize(width, height);
			}
			result = 0;
			wasHandled = true;
			break;

			case WM_PAINT:
			case WM_DISPLAYCHANGE:
			{
				PAINTSTRUCT ps;
				BeginPaint(hwnd, &ps);
				pSimpleD2DApp->OnRender();
				EndPaint(hwnd, &ps);
			}
			result = 0;
			wasHandled = true;
			break;

			case WM_DESTROY:
			{
				PostQuitMessage(0);
			}
			result = 1;
			wasHandled = true;
			break;
			}
		}
		if (!wasHandled) {
			result = DefWindowProc(hwnd, message, wParam, lParam);
		}
	}
	return result;
}

//create a direct2d bitmap from a resource in the application resource file
HRESULT SimpleD2DApp::LoadResourceBitmap(
	ID2D1RenderTarget* pRenderTarget,
	IWICImagingFactory* pIWICFactory,
	PCWSTR resourceName,
	PCWSTR resourceType,
	UINT destinationWidth,
	UINT destinationHeight,
	ID2D1Bitmap** ppBitmap
) {
	HRESULT hr = S_OK;
	IWICBitmapDecoder* pDecoder = NULL;
	IWICBitmapFrameDecode* pSource = NULL;
	IWICStream* pStream = NULL;
	IWICFormatConverter* pConverter = NULL;
	IWICBitmapScaler* pScaler = NULL;

	HRSRC imageResHandle = NULL;
	HGLOBAL imageResDataHandle = NULL;
	void* pImageFile = NULL;
    DWORD imageFileSize = 0;

	//locate the resource 
	imageResHandle = FindResourceW(HINST_THISCOMPONENT, resourceName, resourceType);

	hr = imageResHandle ? S_OK : E_FAIL;
	if (SUCCEEDED(hr)) {
		//load the resource 
		imageResDataHandle = LoadResource(HINST_THISCOMPONENT, imageResHandle);
		hr = imageResDataHandle ? S_OK : E_FAIL;
	}
	if (SUCCEEDED(hr)) {
		//lock it to get a system memory pointer 
		pImageFile = LockResource(imageResDataHandle);
		hr = pImageFile ? S_OK : E_FAIL;
	}
	if (SUCCEEDED(hr)) {
		//calculate the size
		imageFileSize = SizeofResource(HINST_THISCOMPONENT, imageResHandle);
		hr = imageFileSize ? S_OK : E_FAIL;
	}
	if (SUCCEEDED(hr)) {
		//create a wic stream to map onto the memory
		hr = pIWICFactory->CreateStream(&pStream);
	}
	if (SUCCEEDED(hr)) {
		//initialize the stream with the memory pointer and size
		hr = pStream->InitializeFromMemory(
			reinterpret_cast<BYTE*>(pImageFile),
			imageFileSize
		);
	}
	if (SUCCEEDED(hr)) {
		//create a decoder for the stream
		hr = pIWICFactory->CreateDecoderFromStream(
			pStream, NULL, WICDecodeMetadataCacheOnLoad,
			&pDecoder);
	}
	if (SUCCEEDED(hr)) {
		//create the initial frame
		hr = pDecoder->GetFrame(0, &pSource);
	}
	if (SUCCEEDED(hr)) {
		//convert the image format
		hr = pIWICFactory->CreateFormatConverter(&pConverter);
	}
	if (SUCCEEDED(hr)) {
		//if a new width or height was specified,create an
		//IWICBitmapScaler and use it to resize the iamge
		if (destinationWidth != 0 || destinationHeight != 0) {
			UINT originalWidth, originalHeight;
			hr = pSource->GetSize(&originalWidth, &originalHeight);
			if (SUCCEEDED(hr)) {
				if (destinationWidth == 0) {
					FLOAT scalar = static_cast<FLOAT>(destinationHeight) / static_cast<FLOAT>(originalHeight);
					destinationWidth = static_cast<UINT>(scalar * static_cast<FLOAT>(originalWidth));
				}
				else if (destinationHeight == 0) {
					FLOAT scalar = static_cast<FLOAT>(destinationWidth) / static_cast<FLOAT>(originalWidth);
					destinationHeight = static_cast<UINT>(scalar * static_cast<FLOAT>(originalHeight));
				}

				hr = pIWICFactory->CreateBitmapScaler(&pScaler);
				if (SUCCEEDED(hr)) {
					hr = pScaler->Initialize(
						pSource,
						destinationWidth,
						destinationHeight,
						WICBitmapInterpolationModeCubic
					);
					if (SUCCEEDED(hr)) {
						hr = pConverter->Initialize(
							pScaler,
							GUID_WICPixelFormat32bppPBGRA,
							WICBitmapDitherTypeNone,
							NULL,
							0.f,
							WICBitmapPaletteTypeMedianCut
						);
					}
				}
			}
		}
		else {
			hr = pConverter->Initialize(
				pSource,
				GUID_WICPixelFormat32bppBGRA,
				WICBitmapDitherTypeNone,
				NULL,
				0.f,
				WICBitmapPaletteTypeMedianCut
			);
		}
	}
	if (SUCCEEDED(hr)) {
		//create a Direct2D bitmap from the WIC bitmap.
		hr = pRenderTarget->CreateBitmapFromWicBitmap(
			pConverter,
			NULL,
			ppBitmap
		);
	}

	SafeRelease(&pDecoder);
	SafeRelease(&pSource);
	SafeRelease(&pStream);
	SafeRelease(&pConverter);
	SafeRelease(&pScaler);
	return hr;
}

//create a direct2d bitmap from the specified file name 
HRESULT SimpleD2DApp::LoadBitmapFromFile(
	ID2D1RenderTarget* pRenderTarget,
	IWICImagingFactory* pIWICFactory,
	PCWSTR uri,
	UINT destinationWidth,
	UINT destinationHeight,
	ID2D1Bitmap** ppBitmap
) {
	HRESULT hr = S_OK;

	IWICBitmapDecoder* pDecoder = NULL;
	IWICBitmapFrameDecode* pSource = NULL;
	IWICStream* pStream = NULL;
	IWICFormatConverter* pConverter = NULL;
	IWICBitmapScaler* pScaler = NULL;

	hr = pIWICFactory->CreateDecoderFromFilename(
		uri,
		NULL,
		GENERIC_READ,
		WICDecodeMetadataCacheOnLoad,
		&pDecoder
	);
	if (SUCCEEDED(hr)) {
		//create the initial frame 
		hr = pDecoder->GetFrame(0, &pSource);
	}
	if (SUCCEEDED(hr)) {
		//convert the image format
		hr = pIWICFactory->CreateFormatConverter(&pConverter);
	}
	if (SUCCEEDED(hr)) {
		//if a new width or height was specified,create an 
		//IWICBitmapScaler and use it to resize the iamge
		if (destinationWidth == 0 || destinationHeight == 0) {
			UINT originalWidth, originalHeight;
			hr = pSource->GetSize(&originalWidth, &originalHeight);
			if (SUCCEEDED(hr)) {
				if (destinationWidth == 0) {
					FLOAT scalar = static_cast<FLOAT>(destinationHeight) / static_cast<FLOAT>(originalHeight);
					destinationWidth = static_cast<UINT>(scalar * static_cast<FLOAT>(originalWidth));
				} 
				else if (destinationHeight == 0) {
					FLOAT scalar = static_cast<FLOAT>(destinationWidth) / static_cast<FLOAT>(originalWidth);
					destinationHeight = static_cast<UINT>(scalar * static_cast<FLOAT>(originalHeight));
				}
				
				hr = pIWICFactory->CreateBitmapScaler(&pScaler);
				if (SUCCEEDED(hr)) {
					hr = pScaler->Initialize(
						pSource,
						destinationWidth,
						destinationHeight,
						WICBitmapInterpolationModeCubic
					);
				}
				if (SUCCEEDED(hr)) {
					hr = pConverter->Initialize(
						pScaler,
						GUID_WICPixelFormat32bppPBGRA,
						WICBitmapDitherTypeNone,
						NULL,
						0.f,
						WICBitmapPaletteTypeMedianCut
					);
				}
			}
		}
		else { //don't scale the image
			hr = pConverter->Initialize(
				pSource,
				GUID_WICPixelFormat32bppPBGRA,
				WICBitmapDitherTypeNone,
				NULL,
				0.f,
				WICBitmapPaletteTypeMedianCut
			);
		}
	}
	if (SUCCEEDED(hr)) {
		//Create a direct2d bitmap from the wic bitmap
		hr = pRenderTarget->CreateBitmapFromWicBitmap(
			pConverter,
			NULL,
			ppBitmap
		);
	}

	SafeRelease(&pDecoder);
	SafeRelease(&pSource);
	SafeRelease(&pStream);
	SafeRelease(&pConverter);
	SafeRelease(&pScaler);

	return hr;
}