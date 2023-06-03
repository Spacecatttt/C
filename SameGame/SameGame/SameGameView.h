
// SameGameView.h: интерфейс класса CSameGameView
//

#pragma once


class CSameGameView : public CView
{
protected: // создать только из сериализации
	CSameGameView() noexcept;
	DECLARE_DYNCREATE(CSameGameView)

 
public:
	CSameGameDoc* GetDocument() const;

 
 
	virtual void OnDraw(CDC* pDC);  // переопределено для отрисовки этого представления
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

	void setColorCount(int numColors);
	void CSameGameView::chekColor(int numColor, CCmdUI* pCmdUI);

	void ResizeWindow();
	 
	virtual ~CSameGameView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

 

// Созданные функции схемы сообщений
protected:
	DECLARE_MESSAGE_MAP()

public:
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	virtual void OnInitialUpdate();

	afx_msg void On3color();
	afx_msg void OnUpdate3color(CCmdUI* pCmdUI);
	afx_msg void On4color();
	afx_msg void OnUpdate4color(CCmdUI* pCmdUI);
	afx_msg void On5color();
	afx_msg void OnUpdate5color(CCmdUI* pCmdUI);
	afx_msg void On6color();
	afx_msg void OnUpdate6color(CCmdUI* pCmdUI);
	afx_msg void On7color();
	afx_msg void OnUpdate7color(CCmdUI* pCmdUI);
	afx_msg void Onnumber();
	afx_msg void Onsize();

	afx_msg void On32771();
	afx_msg void OnEditUndo();
	afx_msg void OnUpdate32771(CCmdUI* pCmdUI);
	afx_msg void OnUpdateEditUndo(CCmdUI* pCmdUI);
};
 
#ifndef _DEBUG  // версия отладки в SameGameView.cpp
inline CSameGameDoc* CSameGameView::GetDocument() const
   { return reinterpret_cast<CSameGameDoc*>(m_pDocument); }
#endif

