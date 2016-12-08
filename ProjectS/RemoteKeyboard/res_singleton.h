#pragma once
#include "sys_cfg.h"

class ResSingleton
{
public:
	ResSingleton();
	
public:
	static ResSingleton * GetInstance();
	static void DestroyInstance();

	SysCfg * GetSysCfg() { return &sys_cfg_; }

private:
	static ResSingleton * instance_;
	SysCfg sys_cfg_;
};

