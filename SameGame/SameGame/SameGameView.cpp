 
#include "stdafx.h"
#include "pch.h"
#include "framework.h"
#include "Resource.h"
#ifndef SHARED_HANDLERS
#include "SameGame.h"
#endif

#include "SameGameDoc.h"
#include "SameGameView.h"
#include "COptionDialog.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CSameGameView

IMPLEMENT_DYNCREATE(CSameGameView, CView)

BEGIN_MESSAGE_MAP(CSameGameView, CView)
	ON_WM_LBUTTONDOWN()
	ON_WM_ERASEBKGND()
	ON_COMMAND(ID_3color, &CSameGameView::On3color)
	ON_COMMAND(ID_4color, &CSameGameView::On4color)
	ON_COMMAND(ID_5color, &CSameGameView::On5color)
	ON_COMMAND(ID_6color, &CSameGameView::On6color)
	ON_COMMAND(ID_7color, &CSameGameView::On7color)
	ON_UPDATE_COMMAND_UI(ID_3color, &CSameGameView::OnUpdate3color)
	ON_UPDATE_COMMAND_UI(ID_4color, &CSameGameView::OnUpdate4color)
	ON_UPDATE_COMMAND_UI(ID_5color, &CSameGameView::OnUpdate5color)
	ON_UPDATE_COMMAND_UI(ID_6color, &CSameGameView::OnUpdate6color)
	ON_UPDATE_COMMAND_UI(ID_7color, &CSameGameView::OnUpdate7color)
	ON_COMMAND(ID_number, &CSameGameView::Onnumber)
	ON_COMMAND(ID_size, &CSameGameView::Onsize)

	ON_COMMAND(ID_32771, &CSameGameView::On32771)
	ON_UPDATE_COMMAND_UI(ID_32771, &CSameGameView::OnUpdate32771)
	ON_UPDATE_COMMAND_UI(ID_EDIT_UNDO, &CSameGameView::OnUpdateEditUndo)
	ON_COMMAND(ID_EDIT_UNDO, &CSameGameView::OnEditUndo)
END_MESSAGE_MAP()

// Создание или уничтожение CSameGameView

CSameGameView::CSameGameView() noexcept
{
	// TODO: добавьте код создания

}

CSameGameView::~CSameGameView()
{
}

BOOL CSameGameView::PreCreateWindow(CREATESTRUCT& cs)
{
	 

	return CView::PreCreateWindow(cs);
}

// Рисование CSameGameView

void CSameGameView::OnDraw(CDC* pDC)
{
	CSameGameDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	// Сохраняем текущее состояние контекста устройства
	int nDCSave = pDC->SaveDC();

	// Получаем размеры клиентской области
	CRect rcClient;
	GetClientRect(&rcClient);
	COLORREF clr = pDoc->GetBoardSpace(-1, -1);

	// Сначала отрисовываем фон
	pDC->FillSolidRect(&rcClient, clr);

	// Создаем кисть для рисования
	CBrush br;
	br.CreateStockObject(HOLLOW_BRUSH);
	CBrush* pbrOld = pDC->SelectObject(&br);

	// Рисуем блоки
	for (int row = 0; row < pDoc->GetRows(); row++)
	{
		for (int col = 0; col < pDoc->GetColumns(); col++)
		{

			clr = pDoc->GetBoardSpace(row, col);

			// Вычисляем размер и позицию игрового пространства
			CRect rcBlock;
			rcBlock.top = row * pDoc->GetHeight();
			rcBlock.left = col * pDoc->GetWidth();
			rcBlock.right = rcBlock.left + pDoc->GetWidth();
			rcBlock.bottom = rcBlock.top + pDoc->GetHeight();

			// Заполняем блок соответствующим цветом
			pDC->FillSolidRect(&rcBlock, clr);

			// Рисуем контур
			pDC->Rectangle(&rcBlock);
		}
	}
	// Восстанавливаем контекст устройства
	pDC->RestoreDC(nDCSave);
	br.DeleteObject();
} 



// Диагностика CSameGameView

#ifdef _DEBUG
void CSameGameView::AssertValid() const
{
	CView::AssertValid();
}

void CSameGameView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CSameGameDoc* CSameGameView::GetDocument() const // встроена неотлаженная версия
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CSameGameDoc)));
	return (CSameGameDoc*)m_pDocument;
}
#endif //_DEBUG


// Обработчики сообщений CSameGameView
void CSameGameView::OnInitialUpdate()
{
	CView::OnInitialUpdate();

	// Изменяем размеры окна
	ResizeWindow();

}


void CSameGameView::ResizeWindow()
{
	// Создаем указатель на Document
	CSameGameDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// Получаем размеры клиентской области
	CRect rcClient, rcWindow;
	GetClientRect(&rcClient);
	GetParentFrame()->GetWindowRect(&rcWindow);
	int nWidthDiff = rcWindow.Width() - rcClient.Width();
	int nHeightDiff = rcWindow.Height() - rcClient.Height();

	// Изменяем размеры окна, исходя из размеров нашей доски
	rcWindow.right = rcWindow.left +
		pDoc->GetWidth() * pDoc->GetColumns() + nWidthDiff;
	rcWindow.bottom = rcWindow.top +
		pDoc->GetHeight() * pDoc->GetRows() + nHeightDiff;

	// Функция MoveWindow() изменяет размер окна фрейма
	GetParentFrame()->MoveWindow(&rcWindow);
}
void CSameGameView::OnLButtonDown(UINT nFlags, CPoint point)
{
	CSameGameDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	int row = point.y / pDoc->GetHeight();
	int col = point.x / pDoc->GetWidth();
	int count = pDoc->DeleteBlocks(row, col);
	if (count > 0)
	{
		Invalidate();
		UpdateWindow();
		if (pDoc->IsGameOver())
		{
			int remaining = pDoc->GetRemainingCount();
			CString message;
			message.Format(_T("No more moves left\nBlocks remaining: %d"), remaining);
			MessageBox(message, _T("Game Over"), MB_OK | MB_ICONINFORMATION);
		}
	}
	CView::OnLButtonDown(nFlags, point);
}

void CSameGameView::setColorCount(int numColors) {
	CSameGameDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	pDoc->SetNumColors(numColors);
	Invalidate();
	UpdateWindow();
}
void CSameGameView::chekColor(int numColor, CCmdUI* pCmdUI) {
	CSameGameDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// Проверка установленного уровня сложности
	pCmdUI->SetCheck(pDoc->GetNumColors() == numColor);
}
void CSameGameView::On3color()
{
	setColorCount(3);
}


void CSameGameView::OnUpdate3color(CCmdUI* pCmdUI)
{ // Сначала получаем указатель на Document
	chekColor(3, pCmdUI);
}


void CSameGameView::On4color()
{
	setColorCount(4);
}
void CSameGameView::OnUpdate4color(CCmdUI* pCmdUI)
{
	chekColor(4, pCmdUI);
}
void CSameGameView::On5color()
{
	setColorCount(5);
}
void CSameGameView::OnUpdate5color(CCmdUI* pCmdUI)
{
	chekColor(5, pCmdUI);
}
void CSameGameView::On6color()
{
	setColorCount(6);
}
void CSameGameView::OnUpdate6color(CCmdUI* pCmdUI)
{
	chekColor(6, pCmdUI);
}
void CSameGameView::On7color()
{
	setColorCount(7);
}
void CSameGameView::OnUpdate7color(CCmdUI* pCmdUI)
{
	chekColor(7, pCmdUI);
}

void CSameGameView::Onnumber()
{
	CSameGameDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	COptionDialog dlg(true, this);
	dlg.m_nValue1 = pDoc->GetRows();
	dlg.m_nValue2 = pDoc->GetColumns();
	if (dlg.DoModal() == IDOK) {

		pDoc->DeleteBoard();

		 
		pDoc->SetRows(dlg.m_nValue1);
		pDoc->SetColumns(dlg.m_nValue2);

		 
		pDoc->SetupBoard();

	 
		ResizeWindow();
	}
}


void CSameGameView::Onsize()
{
	CSameGameDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	COptionDialog dlg(false, this);
	dlg.m_nValue1 = pDoc->GetWidth();
	dlg.m_nValue2 = pDoc->GetHeight();
	if (dlg.DoModal() == IDOK) {
		pDoc->DeleteBoard();
		pDoc->SetWidth(dlg.m_nValue1);
		pDoc->SetHeight(dlg.m_nValue2);
		pDoc->SetupBoard();
		 ResizeWindow();

	}
}


void CSameGameView::On32771()
{
	CSameGameDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	pDoc->RedoLast();
	Invalidate();
	UpdateWindow();
}


void CSameGameView::OnUpdate32771(CCmdUI* pCmdUI)
{
	CSameGameDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	pCmdUI->Enable(pDoc->CanRedo());
}


void CSameGameView::OnUpdateEditUndo(CCmdUI* pCmdUI)
{
	CSameGameDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	pCmdUI->Enable(pDoc->CanUndo());
}


void CSameGameView::OnEditUndo()
{
	CSameGameDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	pDoc->UndoLast();
	Invalidate();
	UpdateWindow();
}
