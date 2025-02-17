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

#ifndef CHAT_CTRL_H
#define CHAT_CTRL_H

#pragma once

#include <airdcpp/Client.h>
#include <airdcpp/DupeType.h>
#include <airdcpp/Message.h>
#include <airdcpp/UserInfoBase.h>
#include <airdcpp/SortedVector.h>

#include <boost/algorithm/string.hpp>

#include <airdcpp/modules/ColorSettings.h>

#include "ShellContextMenu.h"
#include "TypedListViewCtrl.h"
#include "ImageDataObject.h"
#include "UCHandler.h"
#include "DownloadBaseHandler.h"
#include "UserInfoBaseHandler.h"
#include "UserUtil.h"

class UserInfo;

class RichTextBox : public CRichEditCtrl, public CMessageMap, public UCHandler<RichTextBox>, public DownloadBaseHandler<RichTextBox>, public UserInfoBaseHandler<RichTextBox>, public UserInfoBase
{
	friend class UCHandler<RichTextBox>;
public:

	BEGIN_MSG_MAP(RichTextBox)
		MESSAGE_HANDLER(WM_CONTEXTMENU, onContextMenu)
		MESSAGE_HANDLER(WM_SIZE, onSize)
		MESSAGE_HANDLER(WM_LBUTTONDOWN, onLButtonDown)
		MESSAGE_HANDLER(WM_EXITMENULOOP, onExitMenuLoop)
		MESSAGE_HANDLER(WM_SETCURSOR, onSetCursor)
		MESSAGE_HANDLER(WM_MOUSEMOVE, onMouseMove)
		MESSAGE_HANDLER(WM_FINDREPLACE, onFind)
		MESSAGE_HANDLER(WM_CHAR, onChar)

		MESSAGE_HANDLER(WM_LBUTTONUP, onLeftButtonUp)

		MESSAGE_HANDLER_HWND(WM_MEASUREITEM, OMenu::onMeasureItem)
		MESSAGE_HANDLER_HWND(WM_DRAWITEM, OMenu::onDrawItem)
		MESSAGE_HANDLER(WM_DRAWITEM, ShellMenu::handleDrawItem)
		MESSAGE_HANDLER(WM_MEASUREITEM, ShellMenu::handleMeasureItem)
		MESSAGE_HANDLER(WM_MENUCHAR, ShellMenu::dispatch)
		MESSAGE_HANDLER(WM_INITMENUPOPUP, ShellMenu::handleInitMenuPopup)
		MESSAGE_HANDLER(WM_UNINITMENUPOPUP, ShellMenu::handleUnInitMenuPopup)
		MESSAGE_HANDLER(WM_MENUSELECT, ShellMenu::handleMenuSelect)

		COMMAND_ID_HANDLER(IDC_COPY_ACTUAL_LINE, onCopyActualLine)
		COMMAND_ID_HANDLER(ID_EDIT_COPY, onEditCopy)
		COMMAND_ID_HANDLER(IDC_BAN_IP, onBanIP)
		COMMAND_ID_HANDLER(IDC_UNBAN_IP, onUnBanIP)
		COMMAND_ID_HANDLER(IDC_WHOIS_IP, onWhoisIP)

		COMMAND_ID_HANDLER(IDC_OPEN_USER_LOG, onOpenUserLog)
		COMMAND_ID_HANDLER(IDC_USER_HISTORY, onOpenUserLog)

		COMMAND_RANGE_HANDLER(IDC_COPY, IDC_COPY + UserUtil::COLUMN_LAST, onCopyUserInfo)
		MESSAGE_HANDLER(WM_COMMAND, onCommand)
	END_MSG_MAP()

	RichTextBox();
	~RichTextBox();

	void handleDeleteFile();
	void handleAddAutoSearchFile();
	void handleAddAutoSearchDir();
	void handleSearchDir();
	void OnRButtonDown(POINT pt);

	LRESULT onMouseMove(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM lParam, BOOL& bHandled);
	LRESULT onContextMenu(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/);
	LRESULT onSize(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/);
	LRESULT onLButtonDown(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/);
	LRESULT onCommand(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& /*bHandled*/) { return SendMessage(GetParent(), uMsg, wParam, lParam); }
	LRESULT onLeftButtonUp(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	bool onClientEnLink(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM lParam, BOOL& /*bHandled*/);
	LRESULT onExitMenuLoop(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/);
	LRESULT onSetCursor(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/);

	LRESULT onEditCopy(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/);
	LRESULT onCopyActualLine(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/);
	LRESULT onBanIP(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/);
	LRESULT onUnBanIP(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/);
	LRESULT onWhoisIP(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/);

	LRESULT onOpenUserLog(WORD /*wNotifyCode*/, WORD wID, HWND /*hWndCtl*/, BOOL& /*bHandled*/);

	void handleSearchIP(const tstring& aIP) noexcept;
	void handleEditSelectAll();
	void handleEditClearAll();

	void handleIgnore();
	void handleUnignore();

	void handleOpenLink();

	LRESULT onCopyUserInfo(WORD /*wNotifyCode*/, WORD wID, HWND /*hWndCtl*/, BOOL& /*bHandled*/);

	void handleSearch();
	void handleSearchTTH();

	void handleOpenFile();
	void handleOpenFolder();
	void handleRemoveTemp();

	LRESULT onFind(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM lParam, BOOL& /*bHandled*/);
	LRESULT onChar(UINT uMsg, WPARAM wParam, LPARAM /*lParam*/, BOOL& bHandled);

	void findText(tstring& aTxt=Util::emptyStringT);
	void runUserCommand(UserCommand& uc);

	typedef boost::iterator_range<boost::range_const_iterator<tstring>::type> tstring_range;
	static std::string unicodeEscapeFormatter(const tstring_range& match);
	static tstring rtfEscapeFormatter(const tstring_range& match);

	static std::string escapeUnicode(const tstring& str);
	/// escape Rich Edit control chars: {, }, and \, as well as \n which becomes \line.
	static tstring rtfEscape(const tstring& str);

	LONG AppendText(tstring& sMsg, POINT& pt, LONG& lSelBeginSaved, LONG& lSelEndSaved);
	void SetText(const string& aText, const MessageHighlight::SortedList& aHighlights, bool bUseEmoAndHighligts = false);
	bool AppendMessage(const Message& aMessage, CHARFORMAT2& cf, bool bUseEmo = true);
	// bool AppendChat(const Identity& i, const tstring& sMyNick, const tstring& sTime, tstring sMsg, CHARFORMAT2& cf, bool bUseEmo = true);
	void AppendHTML(const string& aTxt);
	tstring getLinkText(const ENLINK& link);
	LRESULT handleLink(ENLINK& link);

	void setSelectedUser(const tstring& s) { selectedUser = s; }
	const tstring& getSelectedUser() { return selectedUser; }

	size_t	FullTextMatch(ColorSettings* cs, CHARFORMAT2 &cf, const tstring &line, size_t pos, long &lineIndex);
	size_t	RegExpMatch(ColorSettings* cs, CHARFORMAT2 &cf, const tstring &line, long &lineIndex);
	void	CheckAction(ColorSettings* cs, const tstring& line);
	void Subclass() {
		ccw.SubclassWindow(m_hWnd);
		// We wanna control the scrolling...
	}

	UserPtr getTempShareUser() const noexcept;

	IGETSET(ClientPtr, client, Client, nullptr);
	IGETSET(UserPtr, pmUser, PmUser, nullptr);

	typedef std::function<void(OMenu&, const MessageHighlightPtr&)> ContextMenuF;

	IGETSET(bool, autoScrollToEnd, AutoScrollToEnd, true);
	IGETSET(bool, allowClear, AllowClear, false);
	IGETSET(ContextMenuF, contextMenuHandler, ContextMenuHandler, nullptr);

	/* DownloadBaseHandler functions */
	void handleDownload(const string& aTarget, Priority p, bool isRelease);
	int64_t getDownloadSize(bool isWhole);
	bool showDirDialog(string& fileName);
	HintedUser getMagnetSource();

	UserListHandler<RichTextBox> getUserList() { return UserListHandler<RichTextBox>(*this); }

	static void parsePathHighlights(const string& aText, MessageHighlight::SortedList& highlights_) noexcept;
protected:
	// UserInfoBase
	const UserPtr& getUser() const;
	const string& getHubUrl() const;
private:
	void clearSelInfo();
	void updateSelectedText(POINT pt, bool selectLink);
	static UINT	WM_FINDREPLACE;
	TCHAR*		findBuffer;
	const WORD	findBufferSize = 100;

	bool HitNick(const POINT& p, tstring& sNick, int& iBegin , int& iEnd);
	bool HitIP(const POINT& p, tstring& sIP, int& iBegin, int& iEnd);
	bool updateAuthor();
	static void unifyLineEndings(tstring& aText);

	tstring WordFromPos(const POINT& p);
	tstring LineFromPos(const POINT& p) const;
	void FormatLegacyHighlights(tstring& sMsg, LONG lSelBegin);
	void FormatEmoticons(tstring& sText, LONG lSelBegin);
	void FormatHighlights(tstring& aTextT, const string& aText, const MessageHighlight::SortedList& aHighlights, LONG lSelBegin);
	LONG FormatTimestampAuthor(bool aIsThirdPerson, const Identity& aIdentity, const tstring& sTime, CHARFORMAT2& cf, LONG lSelBegin);
	void CheckMessageNotifications(const Message& aMessage);

	void setText(const tstring& text) {
		string tmp = "{\\urtf " + escapeUnicode(rtfEscape(text)) + "}";
		// The cast below isn't a mistake...
		SetTextEx((LPCTSTR)tmp.c_str(), ST_SELECTION, CP_ACP);
	}
	void scrollToEnd();
	
	bool		matchedSound;
	bool		matchedPopup;
	bool		matchedTab;
	bool		logged;
	bool		skipLog;
	bool		timeStamps;

	bool		isPath;
	MessageHighlightPtr selectedHighlight = nullptr;
	bool		isTTH;
	tstring		author;
	int t_height; //text height
	
	bool m_bPopupMenu = false;
	
	OMenu copyMenu;
	CContainedWindow ccw;

	tstring selectedLine;
	tstring selectedIP;
	tstring selectedUser;
	tstring selectedWord;
	uint64_t lastTick;
	bool isLink(POINT& pt);
	bool showHandCursor;

	typedef pair<CHARRANGE, MessageHighlightPtr> ChatLinkPair;

	struct LinkSortOrder {
		int operator()(long left, long right) const {
			return compare(left, right);
		}
	};

	struct LinkStartPos {
		long operator()(const ChatLinkPair& a) const { return a.first.cpMin; }
	};

	typedef SortedVector<ChatLinkPair, deque, long, LinkSortOrder, LinkStartPos> LinkList;
	LinkList links;

	CCursor		handCursor;
	CCursor		arrowCursor;

	void formatSelectedHighlight(const MessageHighlightPtr& aHighlight);
	void formatHighlight(const MessageHighlightPtr& aHighlight, CHARRANGE& ch);
	LinkList::const_reverse_iterator getLink(POINT& pt);
	void openLink(const MessageHighlightPtr& aHighlight);
	string getHighlightDisplayText(const MessageHighlightPtr& aHighlight) const noexcept;
};


#endif //!defined(AFX_CHAT_CTRL_H__595F1372_081B_11D1_890D_00A0244AB9FD__INCLUDED_)
