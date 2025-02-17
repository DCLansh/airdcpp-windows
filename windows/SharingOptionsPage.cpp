/* 
 * Copyright (C) 2011-2023 AirDC++ Project
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
 */

#include "stdafx.h"
#include "Resource.h"

#include "SharingOptionsPage.h"

#include "PropertiesDlg.h"

#include <airdcpp/ShareManager.h>


PropPage::ListItem SharingOptionsPage::listItems[] = {
	{ SettingsManager::SHARE_HIDDEN, ResourceManager::SETTINGS_SHARE_HIDDEN },
	{ SettingsManager::REMOVE_FORBIDDEN, ResourceManager::SETCZDC_REMOVE_FORBIDDEN },
	{ SettingsManager::NO_ZERO_BYTE, ResourceManager::SETTINGS_NO_ZERO_BYTE },
	{ SettingsManager::SKIP_EMPTY_DIRS_SHARE, ResourceManager::DONT_SHARE_EMPTY_DIRS },
	{ SettingsManager::SHARE_FOLLOW_SYMLINKS, ResourceManager::FOLLOW_SYMLINKS },
	{ 0, ResourceManager::LAST }
};

PropPage::TextItem SharingOptionsPage::texts[] = {
	//skiplist
	{ IDC_SB_SKIPLIST_SHARE, ResourceManager::ST_SKIPLIST_SHARE_BORDER },
	{ IDC_ST_SKIPLIST_SHARE_EXT, ResourceManager::ST_SKIPLIST_SHARE },
	{ IDC_SHARE_SKIPLIST_USE_REGEXP, ResourceManager::USE_REGEXP },

	//sharing options
	{ IDC_REFRESHING_OPTIONS, ResourceManager::REFRESH_OPTIONS },
	{ IDC_SETTINGS_MB2, ResourceManager::MiB },
	{ IDC_MINUTES, ResourceManager::MINUTES_LOWER },
	{ IDC_SETTINGS_AUTO_REFRESH_TIME, ResourceManager::SETTINGS_AUTO_REFRESH_TIME },
	{ IDC_SETTINGS_INCOMING_REFRESH_TIME, ResourceManager::SETTINGS_INCOMING_REFRESH_TIME },
	{ IDC_MULTITHREADED_REFRESH_LBL, ResourceManager::MULTITHREADED_REFRESH },
	{ IDC_STARTUP_REFRESH, ResourceManager::SETTINGS_STARTUP_REFRESH },

	{ IDC_DONT_SHARE_BIGGER_THAN, ResourceManager::DONT_SHARE_BIGGER_THAN },
	{ 0, ResourceManager::LAST }
};

PropPage::Item SharingOptionsPage::items[] = {
	//skiplist
	{ IDC_SKIPLIST_SHARE, SettingsManager::SKIPLIST_SHARE, PropPage::T_STR },
	{ IDC_SHARE_SKIPLIST_USE_REGEXP, SettingsManager::SHARE_SKIPLIST_USE_REGEXP, PropPage::T_BOOL },

	//refreshing
	{ IDC_AUTO_REFRESH_TIME, SettingsManager::AUTO_REFRESH_TIME, PropPage::T_INT },
	{ IDC_INCOMING_REFRESH_TIME, SettingsManager::INCOMING_REFRESH_TIME, PropPage::T_INT },
	{ IDC_STARTUP_REFRESH, SettingsManager::STARTUP_REFRESH, PropPage::T_BOOL },

	//general
	{ IDC_DONT_SHARE_BIGGER_VALUE, SettingsManager::MAX_FILE_SIZE_SHARED, PropPage::T_INT },
	{ 0, 0, PropPage::T_END }
};



LRESULT SharingOptionsPage::onInitDialog(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
{
	PropPage::translate((HWND)(*this), texts);
	PropPage::read((HWND)*this, items, listItems, GetDlgItem(IDC_SHARINGLIST));

	//refresh
	setMinMax(IDC_REFRESH_SPIN, 0, 3000);
	setMinMax(IDC_INCOMING_SPIN, 0, 1000);

	ctrlThreadedRefresh.Attach(GetDlgItem(IDC_MULTITHREADED_REFRESH));
	ctrlThreadedRefresh.InsertString(0, CTSTRING(NEVER));
	ctrlThreadedRefresh.InsertString(1, CTSTRING(MANUAL_REFRESHES));
	ctrlThreadedRefresh.InsertString(2, CTSTRING(ALWAYS));
	ctrlThreadedRefresh.SetCurSel(SETTING(REFRESH_THREADING));

	// Do specialized reading here
	return TRUE;
}

void SharingOptionsPage::write() {
	PropPage::write((HWND)*this, items, listItems, GetDlgItem(IDC_SHARINGLIST));
	
	settings->set(SettingsManager::REFRESH_THREADING, ctrlThreadedRefresh.GetCurSel());
}
