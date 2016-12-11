#include "sys_cfg.h"
#include "pugixml.cpp"

SysCfg::SysCfg()
{
}

SysCfg::~SysCfg()
{
}

bool SysCfg::LoadFile(const WCHAR * path)
{
	if (path && wcslen(path) != 0)
		path_ = path;
	else
		path_ = _T("syscfg.xml");

	if (doc_.load_file(path_.c_str())) {
		if (doc_.child(_T("cfginfo")))
			return is_load_ = true;
		doc_.reset();
	}
	return is_load_ = false;
}

bool SysCfg::SetPaht(const WCHAR * path)
{
	if (path && wcslen(path) != 0) {
		path_ = path;
		return true;
	}
	return false;
}

char * SysCfg::WideToMulti(CDuiString wide, char * multi)
{
	ZeroMemory(multi, MAX_PATH);
	int wide_len = wide.GetLength();
	int multi_len = WideCharToMultiByte(CP_ACP, NULL, wide.GetData(), wide_len, NULL, 0, NULL, FALSE);
	::WideCharToMultiByte(CP_ACP, NULL, wide.GetData(), -1, multi, multi_len, NULL, FALSE);
	return multi;
}

CDuiString SysCfg::MultiToWide(string multi)
{
	int multi_len = multi.length();
	int wide_len = ::MultiByteToWideChar(CP_ACP, 0, multi.c_str(), -1, NULL, 0);
	wchar_t *wide_str;
	wide_str = new wchar_t[wide_len + 1];
	memset(wide_str, 0, (wide_len + 1) * sizeof(wchar_t));
	::MultiByteToWideChar(CP_ACP, 0, multi.c_str(), -1, (LPWSTR)wide_str, wide_len);

	CDuiString ret = (wchar_t*)wide_str;
	delete wide_str;

	return ret;
}

bool SysCfg::GetIpInfo(IPSourceType ip_source_type, CDuiString &ip, CDuiString &port)
{

	pugi::xml_node node;
	if(ip_source_type == ServerIP)
		node = GetNode(_T("SarverIP"));
	else
		node = GetNode(_T("BackStreamsIP"));
	pugi::xml_attribute attr_ip = node.attribute(_T("ip"));
	pugi::xml_attribute attr_port = node.attribute(_T("port"));
	if (!attr_ip) {
		attr_ip = node.append_attribute(_T("ip"));
		attr_ip = _T("127.0.0.1");
		SaveFile();
	}
	if (!attr_port) {
		attr_port = node.append_attribute(_T("port"));
		attr_port = _T("12321");
		SaveFile();
	}
	ip = attr_ip.as_string();
	port = attr_port.as_string();
	return true;
}

bool SysCfg::SetIpInfo(IPSourceType ip_source_type, LPCTSTR ip, LPCTSTR port)
{
	pugi::xml_node node;
	if (ip_source_type == ServerIP)
		node = GetNode(_T("SarverIP"));
	else
		node = GetNode(_T("BackStreamsIP"));
	pugi::xml_attribute attr_ip = node.attribute(_T("ip"));
	pugi::xml_attribute attr_port = node.attribute(_T("port"));

	if (!attr_ip)
		attr_ip = node.append_attribute(_T("ip"));
	attr_ip = ip;

	if (!attr_port)
		attr_port = node.append_attribute(_T("port"));
	attr_port = port;

	return SaveFile();
}

RECT SysCfg::GetChBtnPos(LPCTSTR name, int index, HWND hwnd)
{
	pugi::xml_attribute attr = GetNode(name).attribute(_T("pos"));
	if (!attr) {
		RECT win_rect = {};
		GetWindowRect(hwnd, &win_rect);
		UINT w = (win_rect.right - win_rect.left - 90) / 5;
		UINT h = (win_rect.bottom - win_rect.top - 70) / 3;
		TCHAR str_pos[MAX_PATH] = { 0 };
		index -= 3;
		if (index <= 4) {
			_stprintf(str_pos, _T("%d,%d,%d,%d"), index*w, h, index*w + 90, h + 70);
		} else {
			index -= 4;
			_stprintf(str_pos, _T("%d,%d,%d,%d"), index*w, h*2, index*w + 90, h*2 + 70);
		}

		attr = GetNode(name).append_attribute(_T("pos"));
		attr = str_pos;
		SaveFile();
	}

	LPCTSTR pos = attr.as_string();
	LPTSTR pstr = nullptr;
	RECT rect = { 0 };
	rect.left = _tcstol(pos, &pstr, 10);
	rect.top = _tcstol(pstr + 1, &pstr, 10);
	rect.right = _tcstol(pstr + 1, &pstr, 10);
	rect.bottom = _tcstol(pstr + 1, &pstr, 10);

	return rect;
}

bool SysCfg::SetChBtnPos(LPCTSTR name, RECT pos)
{
	TCHAR str_pos[MAX_PATH] = { 0 };
	_stprintf(str_pos, _T("%d,%d,%d,%d"), pos.left, pos.top, pos.right, pos.bottom);
	pugi::xml_attribute attr = GetNode(name).attribute(_T("pos"));
	if (!attr)
		attr = GetNode(name).append_attribute(_T("pos"));
	attr = str_pos;
	return SaveFile();
}

bool SysCfg::SaveFile(const WCHAR * path /* = nullptr */)
{
	if (path)
		return doc_.save_file(path, _T("  "), pugi::format_indent | pugi::format_write_bom, pugi::encoding_utf8);
	else
		return doc_.save_file(path_.c_str(), _T("  "), pugi::format_indent | pugi::format_write_bom, pugi::encoding_utf8);
	return false;
}

pugi::xml_node SysCfg::GetRootNode()
{
	pugi::xml_node node = doc_.child(L"cfginfo");
	if (!node) {
		if (doc_.first_child().type() != pugi::node_declaration) {
			doc_.append_child(pugi::node_declaration).set_name(L"xml version=\"1.0\" encoding=\"utf-8\"");
		}
		node = doc_.append_child(L"cfginfo");
		node.append_attribute(L"name") = L"default";
		node.append_attribute(L"version") = L"1.0";
	}
	return node;
}

pugi::xml_node SysCfg::GetNode(LPCTSTR name)
{
	pugi::xml_node node = GetRootNode().child(name);
	if (!node)
		node = GetRootNode().append_child(name);
	return node;
}
