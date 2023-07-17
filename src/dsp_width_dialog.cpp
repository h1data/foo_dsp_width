#include "stdafx.h"
#include "resource.h"
#include "dsp_width_dialog.h"
#include "dsp_width.h"

BOOL DspWidthDialog::OnInitDialog(CWindow, LPARAM) {
	m_slider = GetDlgItem(IDC_SLIDER);
	m_slider.SetRange(0, RangeTotal);

	{
		dsp_width_params params(0);
		DspWidth::parse_preset(params, m_initData);
		m_slider.SetPos(pfc::clip_t<t_int32>(pfc::rint32(params.width * 1000), RangeMin, RangeMax) - RangeMin);
		RefreshLabel(params.width);
	}
	return TRUE;
}

void DspWidthDialog::OnButton(UINT, int id, CWindow) {
	EndDialog(id);
}

void DspWidthDialog::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar pScrollBar) {
	dsp_width_params params = dsp_width_params((float)(m_slider.GetPos() + RangeMin) * 0.001);

	{
		dsp_preset_impl preset;
		DspWidth::make_preset(params, preset);
		m_callback.on_preset_changed(preset);
	}
	RefreshLabel(params.width);
}

void DspWidthDialog::RefreshLabel(float val) {
	pfc::string_formatter msg; msg << pfc::format_float(val*100, 0U, 1U) << " %";
	::uSetDlgItemText(*this, IDC_SLIDER_LABEL, msg);
}
