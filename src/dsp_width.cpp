#include "stdafx.h"
#include "dsp_width.h"
#include "dsp_width_dialog.h"

DECLARE_COMPONENT_VERSION("Stereo Width", "1.2.0", "Stereo Width DSP component 1.2.0\nby h1data");
VALIDATE_COMPONENT_FILENAME("foo_dsp_width.dll");

void dsp_width_params::set_width(audio_sample width) {
	this->width = width;

	if (width < 1.0) {
		this->c1 = 0.5;
		this->c2 = width * width * 0.5;
	}
	else {
		audio_sample tmp;
		tmp = 1 / (1 + width);
		this->c1 = tmp;
		this->c2 = width * tmp;
	}
}

void DspWidth::on_endofplayback(abort_callback&) { }
void DspWidth::on_endoftrack(abort_callback&) { }
void DspWidth::flush() { }
double DspWidth::get_latency() { return 0; }
bool DspWidth::need_track_change_mark() { return false; }

DspWidth::DspWidth(dsp_preset const& in) : m_params{ dsp_width_params(0.5) } {
	parse_preset(m_params, in);
}

GUID DspWidth::g_get_guid() {
	static const GUID guid =
	{ 0x3e7be68b, 0xf7f3, 0x4024, { 0x87, 0x7e, 0x9b, 0x4c, 0xd3, 0xc9, 0xea, 0x6b } };
	return guid;
}

void DspWidth::g_get_name(pfc::string_base& p_out) {
	p_out = "Stereo Width";
}

bool DspWidth::g_have_config_popup() { return true; }


bool DspWidth::on_chunk(audio_chunk* chunk, abort_callback&) {
	// do nothing mono or surround audio
	if (chunk->get_channel_config() != audio_chunk::channel_config_stereo) return true;

	audio_sample* samples = chunk->get_data();
	audio_sample m, s;
	t_size count = chunk->get_sample_count();
	for (t_size i = 0; i < count; i++) {
		m = (samples[i * 2 + 1] + samples[i * 2]) * m_params.c1;
		s = (samples[i * 2 + 1] - samples[i * 2]) * m_params.c2;
		samples[i * 2] = m - s;
		samples[i * 2 + 1] = m + s;
	}
	chunk->set_data(samples, count, 2, chunk->get_srate());
	return true;
}

bool DspWidth::g_get_default_preset(dsp_preset& p_out) {
	make_preset(dsp_width_params(1.0), p_out);
	return true;
}

void DspWidth::make_preset(dsp_width_params params, dsp_preset& out) {
	dsp_preset_builder builder;
	builder << params.width;
	builder.finish(g_get_guid(), out);
}

void DspWidth::parse_preset(dsp_width_params& params, const dsp_preset& in) {
	try {
		dsp_preset_parser parser(in);
		parser >> params.width;
		params.set_width(params.width);
	}
	catch (exception_io_data) {
		params.set_width(1.00);
	}
}

void DspWidth::g_show_config_popup(const dsp_preset& p_data, HWND p_parent, dsp_preset_edit_callback& p_callback) {
	::RunDSPConfigPopup(p_data, p_parent, p_callback);
}

static void RunDSPConfigPopup(const dsp_preset& p_data, HWND p_parent, dsp_preset_edit_callback& p_callback) {
	DspWidthDialog popup(p_data, p_callback);
	if (popup.DoModal(p_parent) != IDOK) {
		p_callback.on_preset_changed(p_data);
	}
}

static dsp_factory_t<DspWidth> g_dsp_width_factory;
