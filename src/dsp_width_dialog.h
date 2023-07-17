#pragma once
#include "stdafx.h"
#include "resource.h"

class DspWidthDialog : public CDialogImpl<DspWidthDialog> {
public:
	DspWidthDialog(const dsp_preset& initData, dsp_preset_edit_callback& callback) : m_initData(initData), m_callback(callback) { }

	enum { IDD = IDD_DSP };

	enum {
		RangeMin = 0,
		RangeMax = 1000,
		RangeTotal = RangeMax - RangeMin
	};

	BEGIN_MSG_MAP_EX(DspWidthDialog)
		MSG_WM_INITDIALOG(OnInitDialog)
		COMMAND_HANDLER_EX(IDOK, BN_CLICKED, OnButton)
		COMMAND_HANDLER_EX(IDCANCEL, BN_CLICKED, OnButton)
		MSG_WM_HSCROLL(OnHScroll)
	END_MSG_MAP()

private:

	BOOL OnInitDialog(CWindow, LPARAM);
	void OnButton(UINT, int, CWindow);
	void OnHScroll(UINT, UINT, CScrollBar);
	void RefreshLabel(float);

	const dsp_preset& m_initData;
	dsp_preset_edit_callback& m_callback;

	CTrackBarCtrl m_slider;
};
