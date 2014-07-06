#pragma once

#include "stdafx.h"
#include <string>
#include <set>

#include "Base/Event.h"
#include "Base/Thread.h"
#include "Base/RunnableAdapter.h"

#include "AbstractUI.h"
#include "Redis/RedisResult.h"

#include "DuiEx/UIMenu.h"

class CTreeView;

struct TreeKeyContactData
{    
    CTreeNodeUI* pPNode;
    CTreeNodeUI* pNode;
};

class RedisDataUI : public AbstraceUI
{
public:
    struct RedisDataStruct
    {
        int        db;
        CDuiString key;
        CDuiString type;
        CDuiString size;
        RedisResult result;
    };

    RedisDataUI(const CDuiString& strXML, CPaintManagerUI* pm);

    void Initialize();

    int  GetIndex();
    
    CDuiString GetVirtualwndName();

    void RefreshWnd();

    virtual LRESULT HandleCustomMessage( UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled );

    DUI_DECLARE_MESSAGE_MAP()

    virtual void OnClick(TNotifyUI& msg);

    virtual void OnItemClick( TNotifyUI &msg );

    virtual void OnItemActive( TNotifyUI &msg );

    virtual void OnMenuWakeup( TNotifyUI &msg );

    void    OnItemActiveForTree( TNotifyUI &msg );

    void    OnItemActiveForList( TNotifyUI &msg );

    void    OnPaginate(TNotifyUI& msg);

    void    OnCommit(TNotifyUI& msg);

    LRESULT OnDataAdd(HWND hwnd, WPARAM wParam, LPARAM lParam);

    LRESULT OnKeyAdd(HWND hwnd, WPARAM wParam, LPARAM lParam);

    LRESULT OnKeyDel(HWND hwnd, WPARAM wParam, LPARAM lParam);

    LRESULT OnDataVerbose(HWND hwnd, WPARAM wParam, LPARAM lParam);

    bool    OnMenuClick( void* param );
private:    
    void    SetPageValues();

    std::size_t  GetMaxPage();

    void  SetRichEditText(const std::string& text);

    bool  TryJsonFomat(std::string& text);

    bool  TryXMLFormat(std::string& text);

    bool  TryHexFormat(std::string& text);

    RedisResult& GetResult();

public:
    void    DoPaginateWork();

    void    DoRefreshKeysWork();

    void    DoRefreshValuesWork();

    void    BackgroundWorkForRefreshKeys(void);

    void    BackgroundWorkForRefreshValues(void);

private:
    CTreeNodeUI* NewNode(const string& text, bool isLeaf=false);

    void         DelChildNode(CTreeNodeUI* pNode);

private:
    CListUI* m_pList;
    CHorizontalLayoutUI* m_pHorizontalLayout;
    CEditUI*         m_pKeyEdit;
    CEditUI*         m_PTypeEdit;
    CEditUI*         m_pDataSizeEdit;

    CEditUI*         m_pPageCur;
    CButtonUI*       m_pPageFrist;
    CButtonUI*       m_pPageLast;
    CButtonUI*       m_pPageNext;
    CButtonUI*       m_pPageFinal;
    CButtonUI*       m_pCommit;
    CComboUI*        m_pComboFormat;

    CRichEditUI*     m_pRichEdit;
    CTreeNodeUI*     m_pServerInfoNode;

    Base::Event      m_oEventListHeader;
    Base::Event      m_oEventKey;

    static const std::size_t m_PageSize = 100;

    CTreeNodeUI*     m_pAssistNode;  // ����key tree�Ҽ��˵�����ֵΪ��ǰ����Ҽ��Ľڵ�
    RedisDataStruct  m_RedisData;
    Base::Thread     m_Thread;
    std::set<int>    m_UpdateDbs;
    std::auto_ptr< Base::RunnableAdapter<RedisDataUI> > m_pWork;
    
};