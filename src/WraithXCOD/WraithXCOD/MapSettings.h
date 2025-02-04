#pragma once

#define _AFXDLL // AFX Shared DLL
#define _WIN32_WINNT 0x0601 // Windows 7+

#include <afxwin.h>
#include <afxcview.h>
#include <afxext.h>

// We need the resources
#include "resource.h"

// We need the WraithWindow class
#include "WraithWindow.h"

// The COD image settings
class MapSettings : public WraithWindow
{
public:
    // Make a new panel
    MapSettings(CWnd* pParent = NULL) : WraithWindow(IDD_MAPSETTINGS, pParent) { }

private:
    // -- Event delegates

    void OnExportXModels();
    void OnExportObj();
    void OnExportXMB();

protected:

    // Occures when the window is loading
    virtual void OnBeforeLoad();

    // The title font
    CFont TitleFont;

    // Make the map
    DECLARE_MESSAGE_MAP()
};