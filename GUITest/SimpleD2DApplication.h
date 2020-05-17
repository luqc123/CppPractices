#pragma once
#include "CommonHeaders.h"

class SimpleD2DApp {
public:
	SimpleD2DApp();
	~SimpleD2DApp();

	HRESULT Initialize();
	void RunMessageLoop();
private:
	HRESULT CreateDeviceIndependentResource();
	HRESULT CreateDeviceResource();
	HRESULT CreateGridPatternBrush(
		ID2D1RenderTarget* pRenderTarget,
		ID2D1BitmapBrush** ppBitmapBrush
	);

	void DiscardDeviceResource();

	HRESULT OnRender();
	
	void OnResize(
		UINT width,
		UINT height
	);
	static LRESULT CALLBACK WndProc(
		HWND hwnd,
		UINT message,
		WPARAM wParam,
		LPARAM lParam
	);

	HRESULT LoadResourceBitmap(
		ID2D1RenderTarget* pRenderTarget,
		IWICImagingFactory* pIWICFactory,
		PCWSTR resourceName,
		PCWSTR resourceType,
		UINT destinationWidth,
		UINT destinationHeight,
		ID2D1Bitmap** ppBitmap
	);

	HRESULT LoadBitmapFromFile(
		ID2D1RenderTarget* pRenderTarget,
		IWICImagingFactory* pIWICFactory,
		PCWSTR uri,
		UINT destinationWidth,
		UINT destinationHeight,
		ID2D1Bitmap** ppBitmap
	);

private:
	HWND m_hwnd;
	ID2D1Factory* m_pD2DFactory;
	IWICImagingFactory* m_pWICFactory;
	IDWriteFactory* m_pDWriteFactory;
	ID2D1HwndRenderTarget* m_pRenderTarget;
	IDWriteTextFormat* m_pTextFormat;
	ID2D1PathGeometry* m_pPathGeometry;
	ID2D1LinearGradientBrush* m_pLinearGradientBrush;
	ID2D1SolidColorBrush* m_pBlackBrush;
	ID2D1BitmapBrush* m_pGridPatternBitmapBrush;
	ID2D1Bitmap* m_pBitmap;
	ID2D1Bitmap* m_pAnotherBitmap;
};
