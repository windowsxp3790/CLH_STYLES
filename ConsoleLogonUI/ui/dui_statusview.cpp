#include "dui_statusview.h"
#include "spdlog/spdlog.h"
#include "../util/util.h"
#include <winstring.h>
#include "ui_helper.h"
#include "util/interop.h"
#include "resources/resource.h"

void external::StatusView_SetActive(const wchar_t* text)
{
    HideConsoleUI();
    duiManager::SetPageActive((DirectUI::UCString)MAKEINTRESOURCEW(IDUIF_STATUSVIEW));
    //auto statusview = duiManager::Get()->GetWindowOfTypeId<uiStatusView>(4);
    //if (statusview)
    //{
    //    SPDLOG_INFO("Setting active status view instance");
    //    statusview->statusText = text;
    //    statusview->SetActive();
    //}
}

DirectUI::IClassInfo* duiStatusView::Class = NULL;

duiStatusView::duiStatusView()
{
}

duiStatusView::~duiStatusView()
{
}

HRESULT duiStatusView::CreateInstance(DirectUI::Element* rootElement, unsigned long* debugVariable, DirectUI::Element** newElement)
{
    int hr = E_OUTOFMEMORY;

    // Using HeapAlloc instead of new() is required as DirectUI::Element::_DisplayNodeCallback calls HeapFree() with the element
    duiStatusView* instance = (duiStatusView*)HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, sizeof(duiStatusView));

    if (instance != NULL)
    {
        new (instance) duiStatusView();
        hr = instance->Initialize(0, rootElement, debugVariable);
        if (SUCCEEDED(hr))
        {
            *newElement = instance;
        }
        else
        {
            if (instance != NULL)
            {
                instance->Destroy(TRUE);
                instance = NULL;
            }
        }
    }

    return hr;
}

DirectUI::IClassInfo* duiStatusView::GetClassInfoW()
{
    return duiStatusView::Class;
}

void duiStatusView::OnEvent(DirectUI::Event* iev)
{
    if (iev->flag != DirectUI::GMF_BUBBLED)
        return;
    if (!iev->handled)
        DirectUI::Element::OnEvent(iev);

}

void duiStatusView::OnDestroy()
{
    DirectUI::Element::OnDestroy();

}

void duiStatusView::Begin()
{

}