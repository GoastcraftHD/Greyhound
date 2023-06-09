#include "stdafx.h"

// The class we are implementing
#include "MapSettings.h"

// We need the Wraith theme and settings classes
#include "WraithTheme.h"
#include "SettingsManager.h"

// We need the following Wraith classes
#include "Strings.h"

BEGIN_MESSAGE_MAP(MapSettings, WraithWindow)
    ON_COMMAND(IDC_EXPORTXMODELS, OnExportXModels)
    ON_COMMAND(IDC_EXPORTOBJ, OnExportObj)
    ON_COMMAND(IDC_EXPORTXMB, OnExportXMB)
END_MESSAGE_MAP()

void MapSettings::OnBeforeLoad()
{
    // Shift
    ShiftControl(IDC_NOTICE, CRect(0, 1, 0, 0));

    // Make it
    TitleFont.CreateFont(20,           // Height
        0,                             // Width
        0,                             // Escapement
        0,                             // Orientation
        FW_NORMAL,                     // Weight
        FALSE,                         // Italic
        FALSE,                         // Underline
        0,                             // StrikeOut
        ANSI_CHARSET,                  // CharSet
        OUT_DEFAULT_PRECIS,            // OutPrecision
        CLIP_DEFAULT_PRECIS,           // ClipPrecision
        DEFAULT_QUALITY,               // Quality
        DEFAULT_PITCH | FF_SWISS,      // PitchAndFamily
        L"Microsoft Sans Serif");       // Name

    // Set it
    GetDlgItem(IDC_TITLE)->SetFont(&TitleFont);
    GetDlgItem(IDC_TITLE2)->SetFont(&TitleFont);

    // Set tip
    SetControlAnchor(IDC_TIP, 0, 100, 0, 0);
    SetControlAnchor(IDC_NOTICE, 0, 100, 0, 0);

    // Load up configuration
    ((CButton*)GetDlgItem(IDC_EXPORTXMODELS))->SetCheck(SettingsManager::GetSetting("map_exportxmodels", "true") == "true");
    ((CButton*)GetDlgItem(IDC_EXPORTOBJ))->SetCheck(SettingsManager::GetSetting("map_exportobj", "true") == "true");
    ((CButton*)GetDlgItem(IDC_EXPORTXMB))->SetCheck(SettingsManager::GetSetting("map_exportxmb", "true") == "true");
}

void MapSettings::OnExportXModels()
{
    // Whether or not we are checked
    bool CheckboxChecked = ((((CButton*)GetDlgItem(IDC_EXPORTXMODELS))->GetState() & BST_CHECKED) == BST_CHECKED);
    // Set it
    SettingsManager::SetSetting("map_exportxmodels", (CheckboxChecked) ? "true" : "false");
}

void MapSettings::OnExportObj()
{
    // Whether or not we are checked
    bool CheckboxChecked = ((((CButton*)GetDlgItem(IDC_EXPORTOBJ))->GetState() & BST_CHECKED) == BST_CHECKED);
    // Set it
    SettingsManager::SetSetting("map_exportobj", (CheckboxChecked) ? "true" : "false");
}

void MapSettings::OnExportXMB()
{
    // Whether or not we are checked
    bool CheckboxChecked = ((((CButton*)GetDlgItem(IDC_EXPORTXMB))->GetState() & BST_CHECKED) == BST_CHECKED);
    // Set it
    SettingsManager::SetSetting("map_exportxmb", (CheckboxChecked) ? "true" : "false");
}