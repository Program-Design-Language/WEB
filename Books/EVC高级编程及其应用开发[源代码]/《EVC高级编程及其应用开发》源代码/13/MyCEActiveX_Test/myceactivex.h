#if !defined(AFX_MYCEACTIVEX_H__0610C338_465D_4733_897F_13FEA04DAC2F__INCLUDED_)
#define AFX_MYCEACTIVEX_H__0610C338_465D_4733_897F_13FEA04DAC2F__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// Machine generated IDispatch wrapper class(es) created by Microsoft Visual C++

// NOTE: Do not modify the contents of this file.  If this class is regenerated by
//  Microsoft Visual C++, your modifications will be overwritten.

/////////////////////////////////////////////////////////////////////////////
// CMyCEActiveX wrapper class

class CMyCEActiveX : public CWnd
{
protected:
	DECLARE_DYNCREATE(CMyCEActiveX)
public:
	CLSID const& GetClsid()
	{
		static CLSID const clsid
			= { 0x6842371a, 0x9b5a, 0x4b9b, { 0xb3, 0xb4, 0x75, 0x8, 0x39, 0x89, 0x8b, 0xcb } };
		return clsid;
	}
	virtual BOOL Create(LPCTSTR lpszClassName,
		LPCTSTR lpszWindowName, DWORD dwStyle,
		const RECT& rect,
		CWnd* pParentWnd, UINT nID,
		CCreateContext* pContext = NULL)
	{ return CreateControl(GetClsid(), lpszWindowName, dwStyle, rect, pParentWnd, nID); }

    BOOL Create(LPCTSTR lpszWindowName, DWORD dwStyle,
		const RECT& rect, CWnd* pParentWnd, UINT nID,
		CFile* pPersist = NULL, BOOL bStorage = FALSE,
		BSTR bstrLicKey = NULL)
	{ return CreateControl(GetClsid(), lpszWindowName, dwStyle, rect, pParentWnd, nID,
		pPersist, bStorage, bstrLicKey); }

	CString GetMsgContext();
	void SetMsgContext(LPCTSTR);

// Operations
public:
	void ShowMessage();
	void AboutBox();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MYCEACTIVEX_H__0610C338_465D_4733_897F_13FEA04DAC2F__INCLUDED_)
