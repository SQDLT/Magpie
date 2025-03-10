#pragma once
#include "pch.h"


class FrameSourceBase {
public:
	FrameSourceBase() {}

	virtual ~FrameSourceBase() {}

	// 不可复制，不可移动
	FrameSourceBase(const FrameSourceBase&) = delete;
	FrameSourceBase(FrameSourceBase&&) = delete;

	virtual bool Initialize() = 0;

	virtual ComPtr<ID3D11Texture2D> GetOutput() = 0;

	enum class UpdateState {
		NewFrame,
		NoUpdate,
		Waiting,
		Error
	};

	virtual UpdateState Update() = 0;

	virtual bool HasRoundCornerInWin11() = 0;

	virtual bool IsScreenCapture() = 0;

protected:

	// 获取坐标系 1 到坐标系 2 的映射关系
	// 坐标系 1：屏幕坐标系，即虚拟化后的坐标系。原点为屏幕左上角
	// 坐标系 2：虚拟化前的坐标系，即窗口所见的坐标系，原点为窗口左上角
	// 两坐标系为线性映射，a 和 b 返回该映射的参数
	// 如果窗口本身支持高 DPI，则 a 为 1，否则 a 为 DPI 缩放的倒数
	// 此函数是为了将屏幕上的点映射到窗口坐标系中，并且无视 DPI 虚拟化
	// 坐标系 1 中的 (x1, y1) 映射到 (x1 * a + bx, x2 * a + by)
	static bool _GetMapToOriginDPI(HWND hWnd, double& a, double& bx, double& by);

	static bool _CenterWindowIfNecessary(HWND hWnd, const RECT& rcWork);
};
