
#pragma once

#include "defines.h"





// The following functions are used in GUI DPI scaling, so that
// GUIs designed for a 96 DPI setting (i.e. using absolute coords
// or explicit widths/sizes) can continue to run with mostly no issues.

static inline int DPIScale(int x)
{
	extern int g_ScreenDPI;
	return MulDiv(x, g_ScreenDPI, 96);
}

static inline int DPIUnscale(int x)
{
	extern int g_ScreenDPI;
	return MulDiv(x, 96, g_ScreenDPI);
}

//...
//#define IS_PERSISTENT (Hotkey::sHotkeyCount || Hotstring::sHotstringCount || g_KeybdHook || g_MouseHook || g_persistent)

// Since WM_COMMAND IDs must be shared among all menus and controls, they are carefully conserved,
// especially since there are only 65,535 possible IDs.  In addition, they are assigned to ranges
// to minimize the need that they will need to be changed in the future (changing the ID of a main
// menu item, tray menu item, or a user-defined menu item [by way of increasing MAX_CONTROLS_PER_GUI]
// is bad because some scripts might be using PostMessage/SendMessage to automate AutoHotkey itself).
// For this reason, the following ranges are reserved:
// 0: unused (possibly special in some contexts)
// 1: IDOK
// 2: IDCANCEL
// 3 to 1002: GUI window control IDs (these IDs must be unique only within their parent, not across all GUI windows)
// 1003 to 65299: User Defined Menu IDs
// 65300 to 65399: Standard tray menu items.
// 65400 to 65534: main menu items (might be best to leave 65535 unused in case it ever has special meaning)
enum CommandIDs {CONTROL_ID_FIRST = IDCANCEL + 1
	, ID_USER_FIRST = MAX_CONTROLS_PER_GUI + 3 // The first ID available for user defined menu items. Do not change this (see above for why).
	, ID_USER_LAST = 65299  // The last. Especially do not change this due to scripts using Post/SendMessage to automate AutoHotkey.
	, ID_TRAY_FIRST, ID_TRAY_OPEN = ID_TRAY_FIRST
	, ID_TRAY_HELP, ID_TRAY_WINDOWSPY, ID_TRAY_RELOADSCRIPT
	, ID_TRAY_EDITSCRIPT, ID_TRAY_SUSPEND, ID_TRAY_PAUSE, ID_TRAY_EXIT
	, ID_TRAY_LAST = ID_TRAY_EXIT // But this value should never hit the below. There is debug code to enforce.
	, ID_MAIN_FIRST = 65400, ID_MAIN_LAST = 65534}; // These should match the range used by resource.h

#define GUI_INDEX_TO_ID(index) (index + CONTROL_ID_FIRST)
#define GUI_ID_TO_INDEX(id) (id - CONTROL_ID_FIRST) // Returns a small negative if "id" is invalid, such as 0.
#define GUI_HWND_TO_INDEX(hwnd) GUI_ID_TO_INDEX(GetDlgCtrlID(hwnd)) // Returns a small negative on failure (e.g. HWND not found).
// Notes about above:
// 1) Callers should call GuiType::FindControl() instead of GUI_HWND_TO_INDEX() if the hwnd might be a combobox's
//    edit control.
// 2) Testing shows that GetDlgCtrlID() is much faster than looping through a GUI window's control array to find
//    a matching HWND.



enum WinGetCmds {WINGET_CMD_INVALID, WINGET_CMD_ID, WINGET_CMD_IDLAST, WINGET_CMD_PID, WINGET_CMD_PROCESSNAME
	, WINGET_CMD_COUNT, WINGET_CMD_LIST, WINGET_CMD_MINMAX, WINGET_CMD_CONTROLLIST, WINGET_CMD_CONTROLLISTHWND
	, WINGET_CMD_STYLE, WINGET_CMD_EXSTYLE, WINGET_CMD_TRANSPARENT, WINGET_CMD_TRANSCOLOR, WINGET_CMD_PROCESSPATH
};

enum SysGetCmds {SYSGET_CMD_INVALID, SYSGET_CMD_METRICS, SYSGET_CMD_MONITORCOUNT, SYSGET_CMD_MONITORPRIMARY
	, SYSGET_CMD_MONITORAREA, SYSGET_CMD_MONITORWORKAREA, SYSGET_CMD_MONITORNAME
};

enum TransformCmds {TRANS_CMD_INVALID, TRANS_CMD_ASC, TRANS_CMD_CHR, TRANS_CMD_DEREF
	, TRANS_CMD_UNICODE, TRANS_CMD_HTML
	, TRANS_CMD_MOD, TRANS_CMD_POW, TRANS_CMD_EXP, TRANS_CMD_SQRT, TRANS_CMD_LOG, TRANS_CMD_LN
	, TRANS_CMD_ROUND, TRANS_CMD_CEIL, TRANS_CMD_FLOOR, TRANS_CMD_ABS
	, TRANS_CMD_SIN, TRANS_CMD_COS, TRANS_CMD_TAN, TRANS_CMD_ASIN, TRANS_CMD_ACOS, TRANS_CMD_ATAN
	, TRANS_CMD_BITAND, TRANS_CMD_BITOR, TRANS_CMD_BITXOR, TRANS_CMD_BITNOT
	, TRANS_CMD_BITSHIFTLEFT, TRANS_CMD_BITSHIFTRIGHT
};

enum MenuCommands {MENU_CMD_INVALID, MENU_CMD_SHOW, MENU_CMD_USEERRORLEVEL
	, MENU_CMD_ADD, MENU_CMD_RENAME, MENU_CMD_CHECK, MENU_CMD_UNCHECK, MENU_CMD_TOGGLECHECK
	, MENU_CMD_ENABLE, MENU_CMD_DISABLE, MENU_CMD_TOGGLEENABLE
	, MENU_CMD_STANDARD, MENU_CMD_NOSTANDARD, MENU_CMD_COLOR, MENU_CMD_DEFAULT, MENU_CMD_NODEFAULT
	, MENU_CMD_DELETE, MENU_CMD_DELETEALL, MENU_CMD_TIP, MENU_CMD_ICON, MENU_CMD_NOICON
	, MENU_CMD_CLICK, MENU_CMD_MAINWINDOW, MENU_CMD_NOMAINWINDOW
};

#define AHK_LV_SELECT       0x0100
#define AHK_LV_DESELECT     0x0200
#define AHK_LV_FOCUS        0x0400
#define AHK_LV_DEFOCUS      0x0800
#define AHK_LV_CHECK        0x1000
#define AHK_LV_UNCHECK      0x2000
#define AHK_LV_DROPHILITE   0x4000
#define AHK_LV_UNDROPHILITE 0x8000
// Although there's no room remaining in the BYTE for LVIS_CUT (AHK_LV_CUT) [assuming it's ever needed],
// it might be possible to squeeze more info into it as follows:
// Each pair of bits can represent three values (other than zero).  But since only two values are needed
// (since an item can't be both selected an deselected simultaneously), one value in each pair is available
// for future use such as LVIS_CUT.

enum GuiCommands {GUI_CMD_INVALID, GUI_CMD_OPTIONS, GUI_CMD_ADD, GUI_CMD_MARGIN, GUI_CMD_MENU
	, GUI_CMD_SHOW, GUI_CMD_SUBMIT, GUI_CMD_CANCEL, GUI_CMD_MINIMIZE, GUI_CMD_MAXIMIZE, GUI_CMD_RESTORE
	, GUI_CMD_DESTROY, GUI_CMD_FONT, GUI_CMD_TAB, GUI_CMD_LISTVIEW, GUI_CMD_TREEVIEW, GUI_CMD_DEFAULT
	, GUI_CMD_COLOR, GUI_CMD_FLASH, GUI_CMD_NEW
};

enum GuiControlCmds {GUICONTROL_CMD_INVALID, GUICONTROL_CMD_OPTIONS, GUICONTROL_CMD_CONTENTS, GUICONTROL_CMD_TEXT
	, GUICONTROL_CMD_MOVE, GUICONTROL_CMD_MOVEDRAW, GUICONTROL_CMD_FOCUS, GUICONTROL_CMD_ENABLE, GUICONTROL_CMD_DISABLE
	, GUICONTROL_CMD_SHOW, GUICONTROL_CMD_HIDE, GUICONTROL_CMD_CHOOSE, GUICONTROL_CMD_CHOOSESTRING
	, GUICONTROL_CMD_FONT
};

enum GuiControlGetCmds {GUICONTROLGET_CMD_INVALID, GUICONTROLGET_CMD_CONTENTS, GUICONTROLGET_CMD_POS
	, GUICONTROLGET_CMD_FOCUS, GUICONTROLGET_CMD_FOCUSV, GUICONTROLGET_CMD_ENABLED, GUICONTROLGET_CMD_VISIBLE
	, GUICONTROLGET_CMD_HWND, GUICONTROLGET_CMD_NAME
};

typedef UCHAR GuiControls;
enum GuiControlTypes {GUI_CONTROL_INVALID // GUI_CONTROL_INVALID must be zero due to things like ZeroMemory() on the struct.
	, GUI_CONTROL_TEXT, GUI_CONTROL_PIC, GUI_CONTROL_GROUPBOX
	, GUI_CONTROL_BUTTON, GUI_CONTROL_CHECKBOX, GUI_CONTROL_RADIO
	, GUI_CONTROL_DROPDOWNLIST, GUI_CONTROL_COMBOBOX
	, GUI_CONTROL_LISTBOX, GUI_CONTROL_LISTVIEW, GUI_CONTROL_TREEVIEW
	, GUI_CONTROL_EDIT, GUI_CONTROL_DATETIME, GUI_CONTROL_MONTHCAL, GUI_CONTROL_HOTKEY
	, GUI_CONTROL_UPDOWN, GUI_CONTROL_SLIDER, GUI_CONTROL_PROGRESS, GUI_CONTROL_TAB, GUI_CONTROL_TAB2
	, GUI_CONTROL_ACTIVEX, GUI_CONTROL_LINK, GUI_CONTROL_CUSTOM, GUI_CONTROL_STATUSBAR}; // Kept last to reflect it being bottommost in switch()s (for perf), since not too often used.

enum ThreadCommands {THREAD_CMD_INVALID, THREAD_CMD_PRIORITY, THREAD_CMD_INTERRUPT, THREAD_CMD_NOTIMERS};

#define PROCESS_PRIORITY_LETTERS _T("LBNAHR")
enum ProcessCmds {PROCESS_CMD_INVALID, PROCESS_CMD_EXIST, PROCESS_CMD_CLOSE, PROCESS_CMD_PRIORITY
	, PROCESS_CMD_WAIT, PROCESS_CMD_WAITCLOSE};

enum ControlCmds {CONTROL_CMD_INVALID, CONTROL_CMD_CHECK, CONTROL_CMD_UNCHECK
	, CONTROL_CMD_ENABLE, CONTROL_CMD_DISABLE, CONTROL_CMD_SHOW, CONTROL_CMD_HIDE
	, CONTROL_CMD_STYLE, CONTROL_CMD_EXSTYLE
	, CONTROL_CMD_SHOWDROPDOWN, CONTROL_CMD_HIDEDROPDOWN
	, CONTROL_CMD_TABLEFT, CONTROL_CMD_TABRIGHT
	, CONTROL_CMD_ADD, CONTROL_CMD_DELETE, CONTROL_CMD_CHOOSE
	, CONTROL_CMD_CHOOSESTRING, CONTROL_CMD_EDITPASTE};

enum ControlGetCmds {CONTROLGET_CMD_INVALID, CONTROLGET_CMD_CHECKED, CONTROLGET_CMD_ENABLED
	, CONTROLGET_CMD_VISIBLE, CONTROLGET_CMD_TAB, CONTROLGET_CMD_FINDSTRING
	, CONTROLGET_CMD_CHOICE, CONTROLGET_CMD_LIST, CONTROLGET_CMD_LINECOUNT, CONTROLGET_CMD_CURRENTLINE
	, CONTROLGET_CMD_CURRENTCOL, CONTROLGET_CMD_LINE, CONTROLGET_CMD_SELECTED
	, CONTROLGET_CMD_STYLE, CONTROLGET_CMD_EXSTYLE, CONTROLGET_CMD_HWND};

enum DriveCmds {DRIVE_CMD_INVALID, DRIVE_CMD_EJECT, DRIVE_CMD_LOCK, DRIVE_CMD_UNLOCK, DRIVE_CMD_LABEL};

enum DriveGetCmds {DRIVEGET_CMD_INVALID, DRIVEGET_CMD_LIST, DRIVEGET_CMD_FILESYSTEM, DRIVEGET_CMD_LABEL
	, DRIVEGET_CMD_SETLABEL, DRIVEGET_CMD_SERIAL, DRIVEGET_CMD_TYPE, DRIVEGET_CMD_STATUS
	, DRIVEGET_CMD_STATUSCD, DRIVEGET_CMD_CAPACITY};

enum WinSetAttributes {WINSET_INVALID, WINSET_TRANSPARENT, WINSET_TRANSCOLOR, WINSET_ALWAYSONTOP
	, WINSET_BOTTOM, WINSET_TOP, WINSET_STYLE, WINSET_EXSTYLE, WINSET_REDRAW, WINSET_ENABLE, WINSET_DISABLE
	, WINSET_REGION};



#define MAX_MENU_NAME_LENGTH MAX_PATH // For both menu and menu item names.
class UserMenuItem;  // Forward declaration since classes use each other (i.e. a menu *item* can have a submenu).
class UserMenu
{
public:
	LPTSTR mName;  // Dynamically allocated.
	UserMenuItem *mFirstMenuItem, *mLastMenuItem, *mDefault;
	// Keep any fields that aren't an even multiple of 4 adjacent to each other.  This conserves memory
	// due to byte-alignment:
	bool mIncludeStandardItems;
	int mClickCount; // How many clicks it takes to trigger the default menu item.  2 = double-click
	UINT mMenuItemCount;  // The count of user-defined menu items (doesn't include the standard items, if present).
	UserMenu *mNextMenu;  // Next item in linked list
	HMENU mMenu;
	MenuTypeType mMenuType; // MENU_TYPE_POPUP (via CreatePopupMenu) vs. MENU_TYPE_BAR (via CreateMenu).
	HBRUSH mBrush;   // Background color to apply to menu.
	COLORREF mColor; // The color that corresponds to the above.

	// Don't overload new and delete operators in this case since we want to use real dynamic memory
	// (since menus can be read in from a file, destroyed and recreated, over and over).

	UserMenu(LPTSTR aName) // Constructor
		: mName(aName), mFirstMenuItem(NULL), mLastMenuItem(NULL), mDefault(NULL)
		, mIncludeStandardItems(false), mClickCount(2), mMenuItemCount(0), mNextMenu(NULL), mMenu(NULL)
		, mMenuType(MENU_TYPE_POPUP) // The MENU_TYPE_NONE flag is not used in this context.  Default = POPUP.
		, mBrush(NULL), mColor(CLR_DEFAULT)
	{
	}

	ResultType AddItem(LPTSTR aName, UINT aMenuID, Label *aLabel, UserMenu *aSubmenu, LPTSTR aOptions);
	ResultType DeleteItem(UserMenuItem *aMenuItem, UserMenuItem *aMenuItemPrev);
	ResultType DeleteAllItems();
	ResultType ModifyItem(UserMenuItem *aMenuItem, Label *aLabel, UserMenu *aSubmenu, LPTSTR aOptions);
	void UpdateOptions(UserMenuItem *aMenuItem, LPTSTR aOptions);
	ResultType RenameItem(UserMenuItem *aMenuItem, LPTSTR aNewName);
	ResultType UpdateName(UserMenuItem *aMenuItem, LPTSTR aNewName);
	ResultType CheckItem(UserMenuItem *aMenuItem);
	ResultType UncheckItem(UserMenuItem *aMenuItem);
	ResultType ToggleCheckItem(UserMenuItem *aMenuItem);
	ResultType EnableItem(UserMenuItem *aMenuItem);
	ResultType DisableItem(UserMenuItem *aMenuItem);
	ResultType ToggleEnableItem(UserMenuItem *aMenuItem);
	ResultType SetDefault(UserMenuItem *aMenuItem = NULL);
	ResultType IncludeStandardItems();
	ResultType ExcludeStandardItems();
	ResultType Create(MenuTypeType aMenuType = MENU_TYPE_NONE); // NONE means UNSPECIFIED in this context.
	void SetColor(LPTSTR aColorName, bool aApplyToSubmenus);
	void ApplyColor(bool aApplyToSubmenus);
	ResultType AppendStandardItems();
	ResultType Destroy();
	ResultType Display(bool aForceToForeground = true, int aX = COORD_UNSPECIFIED, int aY = COORD_UNSPECIFIED);
	UINT GetSubmenuPos(HMENU ahMenu);
	UINT GetItemPos(LPTSTR aMenuItemName);
	bool ContainsMenu(UserMenu *aMenu);
	void UpdateAccelerators();
	// L17: Functions for menu icons.
	ResultType SetItemIcon(UserMenuItem *aMenuItem, LPTSTR aFilename, int aIconNumber, int aWidth);
	ResultType ApplyItemIcon(UserMenuItem *aMenuItem);
	ResultType RemoveItemIcon(UserMenuItem *aMenuItem);
	static BOOL OwnerMeasureItem(LPMEASUREITEMSTRUCT aParam);
	static BOOL OwnerDrawItem(LPDRAWITEMSTRUCT aParam);
};



class UserMenuItem
{
public:
	LPTSTR mName;  // Dynamically allocated.
	size_t mNameCapacity;
	UINT mMenuID;
	Label *mLabel;
	UserMenu *mSubmenu;
	UserMenu *mMenu;  // The menu to which this item belongs.  Needed to support script var A_ThisMenu.
	int mPriority;
	// Keep any fields that aren't an even multiple of 4 adjacent to each other.  This conserves memory
	// due to byte-alignment:
	bool mEnabled, mChecked;
	UserMenuItem *mNextMenuItem;  // Next item in linked list
	
	union
	{
		// L17: Implementation of menu item icons is OS-dependent (g_os.IsWinVistaOrLater()).
		
		// Older versions of Windows do not support alpha channels in menu item bitmaps, so owner-drawing
		// must be used for icons with transparent backgrounds to appear correctly. Owner-drawing also
		// prevents the icon colours from inverting when the item is selected. DrawIcon() gives the best
		// results, so we store the icon handle as is.
		//
		HICON mIcon;
		
		// Windows Vista and later support alpha channels via 32-bit bitmaps. Since owner-drawing prevents
		// visual styles being applied to menus, we convert each icon to a 32-bit bitmap, calculating the
		// alpha channel as necessary. This is done only once, when the icon is initially set.
		//
		HBITMAP mBitmap;
	};

	// Constructor:
	UserMenuItem(LPTSTR aName, size_t aNameCapacity, UINT aMenuID, Label *aLabel, UserMenu *aSubmenu, UserMenu *aMenu);

	// Don't overload new and delete operators in this case since we want to use real dynamic memory
	// (since menus can be read in from a file, destroyed and recreated, over and over).
};



struct FontType
{
	#define MAX_FONT_NAME_LENGTH 63  // Longest name I've seen is 29 chars, "Franklin Gothic Medium Italic". Anyway, there's protection against overflow.
	TCHAR name[MAX_FONT_NAME_LENGTH + 1];
	// Keep any fields that aren't an even multiple of 4 adjacent to each other.  This conserves memory
	// due to byte-alignment:
	bool italic;
	bool underline;
	bool strikeout;
	int point_size; // Decided to use int vs. float to simplify the code in many places. Fractional sizes seem rarely needed.
	int weight;
	DWORD quality; // L19: Allow control over font quality (anti-aliasing, etc.).
	HFONT hfont;
};

#define	LV_REMOTE_BUF_SIZE 1024  // 8192 (below) seems too large in hindsight, given that an LV can only display the first 260 chars in a field.
#define LV_TEXT_BUF_SIZE 8192  // Max amount of text in a ListView sub-item.  Somewhat arbitrary: not sure what the real limit is, if any.
enum LVColTypes {LV_COL_TEXT, LV_COL_INTEGER, LV_COL_FLOAT}; // LV_COL_TEXT must be zero so that it's the default with ZeroMemory.
struct lv_col_type
{
	UCHAR type;             // UCHAR vs. enum LVColTypes to save memory.
	bool sort_disabled;     // If true, clicking the column will have no automatic sorting effect.
	UCHAR case_sensitive;   // Ignored if type isn't LV_COL_TEXT.  SCS_INSENSITIVE is the default.
	bool unidirectional;    // Sorting cannot be reversed/toggled.
	bool prefer_descending; // Whether this column defaults to descending order (on first click or for unidirectional).
};

struct lv_attrib_type
{
	int sorted_by_col; // Index of column by which the control is currently sorted (-1 if none).
	bool is_now_sorted_ascending; // The direction in which the above column is currently sorted.
	bool no_auto_sort; // Automatic sorting disabled.
	#define LV_MAX_COLUMNS 200
	lv_col_type col[LV_MAX_COLUMNS];
	int col_count; // Number of columns currently in the above array.
	int row_count_hint;
};

typedef UCHAR TabControlIndexType;
typedef UCHAR TabIndexType;
// Keep the below in sync with the size of the types above:
#define MAX_TAB_CONTROLS 255  // i.e. the value 255 itself is reserved to mean "doesn't belong to a tab".
#define MAX_TABS_PER_CONTROL 256
struct GuiControlType
{
	HWND hwnd;
	// Keep any fields that are smaller than 4 bytes adjacent to each other.  This conserves memory
	// due to byte-alignment.  It has been verified to save 4 bytes per struct in this case:
	GuiControls type;
	#define GUI_CONTROL_ATTRIB_IMPLICIT_CANCEL     0x01
	#define GUI_CONTROL_ATTRIB_ALTSUBMIT           0x02
	#define GUI_CONTROL_ATTRIB_LABEL_IS_RUNNING    0x04
	#define GUI_CONTROL_ATTRIB_EXPLICITLY_HIDDEN   0x08
	#define GUI_CONTROL_ATTRIB_EXPLICITLY_DISABLED 0x10
	#define GUI_CONTROL_ATTRIB_BACKGROUND_DEFAULT  0x20 // i.e. Don't conform to window/control background color; use default instead.
	#define GUI_CONTROL_ATTRIB_BACKGROUND_TRANS    0x40 // i.e. Leave this control's background transparent.
	#define GUI_CONTROL_ATTRIB_ALTBEHAVIOR         0x80 // For sliders: Reverse/Invert the value. Also for up-down controls (ALT means 32-bit vs. 16-bit). Also for ListView and Tab, and for Edit.
	UCHAR attrib; // A field of option flags/bits defined above.
	TabControlIndexType tab_control_index; // Which tab control this control belongs to, if any.
	TabIndexType tab_index; // For type==TAB, this stores the tab control's index.  For other types, it stores the page.
	Var *output_var;
	Label *jump_to_label;
	union
	{
		COLORREF union_color;  // Color of the control's text.
		HBITMAP union_hbitmap; // For PIC controls, stores the bitmap.
		// Note: Pic controls cannot obey the text color, but they can obey the window's background
		// color if the picture's background is transparent (at least in the case of icons on XP).
		lv_attrib_type *union_lv_attrib; // For ListView: Some attributes and an array of columns.
	};
	#define USES_FONT_AND_TEXT_COLOR(type) !(type == GUI_CONTROL_PIC || type == GUI_CONTROL_UPDOWN \
		|| type == GUI_CONTROL_SLIDER || type == GUI_CONTROL_PROGRESS)
};

struct GuiControlOptionsType
{
	DWORD style_add, style_remove, exstyle_add, exstyle_remove, listview_style;
	int listview_view; // Viewing mode, such as LVS_ICON, LVS_REPORT.  Int vs. DWORD to more easily use any negative value as "invalid".
	HIMAGELIST himagelist;
	Var *hwnd_output_var; // v1.0.46.01: Allows a script to retrieve the control's HWND upon creation of control.
	int x, y, width, height;  // Position info.
	float row_count;
	int choice;  // Which item of a DropDownList/ComboBox/ListBox to initially choose.
	int range_min, range_max;  // Allowable range, such as for a slider control.
	int tick_interval; // The interval at which to draw tickmarks for a slider control.
	int line_size, page_size; // Also for slider.
	int thickness;  // Thickness of slider's thumb.
	int tip_side; // Which side of the control to display the tip on (0 to use default side).
	GuiControlType *buddy1, *buddy2;
	COLORREF color_listview; // Used only for those controls that need control.union_color for something other than color.
	COLORREF color_bk; // Control's background color.
	int limit;   // The max number of characters to permit in an edit or combobox's edit (also used by ListView).
	int hscroll_pixels;  // The number of pixels for a listbox's horizontal scrollbar to be able to scroll.
	int checked; // When zeroed, struct contains default starting state of checkbox/radio, i.e. BST_UNCHECKED.
	int icon_number; // Which icon of a multi-icon file to use.  Zero means use-default, i.e. the first icon.
	#define GUI_MAX_TABSTOPS 50
	UINT tabstop[GUI_MAX_TABSTOPS]; // Array of tabstops for the interior of a multi-line edit control.
	UINT tabstop_count;  // The number of entries in the above array.
	SYSTEMTIME sys_time[2]; // Needs to support 2 elements for MONTHCAL's multi/range mode.
	SYSTEMTIME sys_time_range[2];
	DWORD gdtr, gdtr_range; // Used in connection with sys_time and sys_time_range.
	ResultType redraw;  // Whether the state of WM_REDRAW should be changed.
	TCHAR password_char; // When zeroed, indicates "use default password" for an edit control with the password style.
	bool range_changed;
	bool color_changed; // To discern when a control has been put back to the default color. [v1.0.26]
	bool start_new_section;
	bool use_theme; // v1.0.32: Provides the means for the window's current setting of mUseTheme to be overridden.
	bool listview_no_auto_sort; // v1.0.44: More maintainable and frees up GUI_CONTROL_ATTRIB_ALTBEHAVIOR for other uses.
	ATOM customClassAtom;
};

LRESULT CALLBACK GuiWindowProc(HWND hWnd, UINT iMsg, WPARAM wParam, LPARAM lParam);
LRESULT CALLBACK TabWindowProc(HWND hWnd, UINT iMsg, WPARAM wParam, LPARAM lParam);

class GuiType
{
public:
	#define GUI_STANDARD_WIDTH_MULTIPLIER 15 // This times font size = width, if all other means of determining it are exhausted.
	#define GUI_STANDARD_WIDTH DPIScale(GUI_STANDARD_WIDTH_MULTIPLIER * sFont[mCurrentFontIndex].point_size)
	// Update for v1.0.21: Reduced it to 8 vs. 9 because 8 causes the height each edit (with the
	// default style) to exactly match that of a Combo or DropDownList.  This type of spacing seems
	// to be what other apps use too, and seems to make edits stand out a little nicer:
	#define GUI_CTL_VERTICAL_DEADSPACE DPIScale(8)
	#define PROGRESS_DEFAULT_THICKNESS DPIScale(2 * sFont[mCurrentFontIndex].point_size)
	LPTSTR mName;
	HWND mHwnd, mStatusBarHwnd;
	HWND mOwner;  // The window that owns this one, if any.  Note that Windows provides no way to change owners after window creation.
	// Control IDs are higher than their index in the array by the below amount.  This offset is
	// necessary because windows that behave like dialogs automatically return IDOK and IDCANCEL in
	// response to certain types of standard actions:
	GuiIndexType mControlCount;
	GuiIndexType mControlCapacity; // How many controls can fit into the current memory size of mControl.
	GuiControlType *mControl; // Will become an array of controls when the window is first created.
	GuiIndexType mDefaultButtonIndex; // Index vs. pointer is needed for some things.
	ULONG mReferenceCount; // For keeping this structure in memory during execution of the Gui's labels.
	Label *mLabelForClose, *mLabelForEscape, *mLabelForSize, *mLabelForDropFiles, *mLabelForContextMenu;
	bool mLabelForCloseIsRunning, mLabelForEscapeIsRunning, mLabelForSizeIsRunning; // DropFiles doesn't need one of these.
	bool mLabelsHaveBeenSet;
	DWORD mStyle, mExStyle; // Style of window.
	bool mInRadioGroup; // Whether the control currently being created is inside a prior radio-group.
	bool mUseTheme;  // Whether XP theme and styles should be applied to the parent window and subsequently added controls.
	TCHAR mDelimiter;  // The default field delimiter when adding items to ListBox, DropDownList, ListView, etc.
	GuiControlType *mCurrentListView, *mCurrentTreeView; // The ListView and TreeView upon which the LV/TV functions operate.
	int mCurrentFontIndex;
	COLORREF mCurrentColor;       // The default color of text in controls.
	COLORREF mBackgroundColorWin; // The window's background color itself.
	COLORREF mBackgroundColorCtl; // Background color for controls.
	HBRUSH mBackgroundBrushWin;   // Brush corresponding to mBackgroundColorWin.
	HBRUSH mBackgroundBrushCtl;   // Brush corresponding to mBackgroundColorCtl.
	HDROP mHdrop;                 // Used for drag and drop operations.
	HICON mIconEligibleForDestruction; // The window's icon, which can be destroyed when the window is destroyed if nothing else is using it.
	HICON mIconEligibleForDestructionSmall; // L17: A window may have two icons: ICON_SMALL and ICON_BIG.
	HACCEL mAccel; // Keyboard accelerator table.
	int mMarginX, mMarginY, mPrevX, mPrevY, mPrevWidth, mPrevHeight, mMaxExtentRight, mMaxExtentDown
		, mSectionX, mSectionY, mMaxExtentRightSection, mMaxExtentDownSection;
	LONG mMinWidth, mMinHeight, mMaxWidth, mMaxHeight;
	TabControlIndexType mTabControlCount;
	TabControlIndexType mCurrentTabControlIndex; // Which tab control of the window.
	TabIndexType mCurrentTabIndex;// Which tab of a tab control is currently the default for newly added controls.
	bool mGuiShowHasNeverBeenDone, mFirstActivation, mShowIsInProgress, mDestroyWindowHasBeenCalled;
	bool mControlWidthWasSetByContents; // Whether the most recently added control was auto-width'd to fit its contents.
	bool mUsesDPIScaling; // Whether the GUI uses DPI scaling.

	#define MAX_GUI_FONTS 200  // v1.0.44.14: Increased from 100 to 200 due to feedback that 100 wasn't enough.  But to alleviate memory usage, the array is now allocated upon first use.
	static FontType *sFont; // An array of structs, allocated upon first use.
	static int sFontCount;
	static HWND sTreeWithEditInProgress; // Needed because TreeView's edit control for label-editing conflicts with IDOK (default button).

	// Don't overload new and delete operators in this case since we want to use real dynamic memory
	// (since GUIs can be destroyed and recreated, over and over).

	// Keep the default destructor to avoid entering the "Law of the Big Three": If your class requires a
	// copy constructor, copy assignment operator, or a destructor, then it very likely will require all three.

	GuiType() // Constructor
		: mName(NULL), mHwnd(NULL), mStatusBarHwnd(NULL), mControlCount(0), mControlCapacity(0)
		, mDefaultButtonIndex(-1), mLabelForClose(NULL), mLabelForEscape(NULL), mLabelForSize(NULL)
		, mLabelForDropFiles(NULL), mLabelForContextMenu(NULL), mReferenceCount(1)
		, mLabelForCloseIsRunning(false), mLabelForEscapeIsRunning(false), mLabelForSizeIsRunning(false)
		, mLabelsHaveBeenSet(false), mUsesDPIScaling(true)
		// The styles DS_CENTER and DS_3DLOOK appear to be ineffectual in this case.
		// Also note that WS_CLIPSIBLINGS winds up on the window even if unspecified, which is a strong hint
		// that it should always be used for top level windows across all OSes.  Usenet posts confirm this.
		// Also, it seems safer to have WS_POPUP under a vague feeling that it seems to apply to dialog
		// style windows such as this one, and the fact that it also allows the window's caption to be
		// removed, which implies that POPUP windows are more flexible than OVERLAPPED windows.
		, mStyle(WS_POPUP|WS_CLIPSIBLINGS|WS_CAPTION|WS_SYSMENU|WS_MINIMIZEBOX) // WS_CLIPCHILDREN (doesn't seem helpful currently)
		, mExStyle(0) // This and the above should not be used once the window has been created since they might get out of date.
		, mInRadioGroup(false), mUseTheme(true), mOwner(NULL), mDelimiter('|')
		, mCurrentFontIndex(FindOrCreateFont()) // Must call this in constructor to ensure sFont array is never NULL while a GUI object exists.  Omit params to tell it to find or create DEFAULT_GUI_FONT.
		, mCurrentListView(NULL), mCurrentTreeView(NULL)
		, mTabControlCount(0), mCurrentTabControlIndex(MAX_TAB_CONTROLS), mCurrentTabIndex(0)
		, mCurrentColor(CLR_DEFAULT)
		, mBackgroundColorWin(CLR_DEFAULT), mBackgroundBrushWin(NULL)
		, mBackgroundColorCtl(CLR_DEFAULT), mBackgroundBrushCtl(NULL)
		, mHdrop(NULL), mIconEligibleForDestruction(NULL), mIconEligibleForDestructionSmall(NULL)
		, mAccel(NULL)
		, mMarginX(COORD_UNSPECIFIED), mMarginY(COORD_UNSPECIFIED) // These will be set when the first control is added.
		, mPrevX(0), mPrevY(0)
		, mPrevWidth(0), mPrevHeight(0) // Needs to be zero for first control to start off at right offset.
		, mMaxExtentRight(0), mMaxExtentDown(0)
		, mSectionX(COORD_UNSPECIFIED), mSectionY(COORD_UNSPECIFIED)
		, mMaxExtentRightSection(COORD_UNSPECIFIED), mMaxExtentDownSection(COORD_UNSPECIFIED)
		, mMinWidth(COORD_UNSPECIFIED), mMinHeight(COORD_UNSPECIFIED)
		, mMaxWidth(COORD_UNSPECIFIED), mMaxHeight(COORD_UNSPECIFIED)
		, mGuiShowHasNeverBeenDone(true), mFirstActivation(true), mShowIsInProgress(false)
		, mDestroyWindowHasBeenCalled(false), mControlWidthWasSetByContents(false)
	{
		// The array of controls is left uninitialized to catch bugs.  Each control's attributes should be
		// fully populated when it is created.
		//ZeroMemory(mControl, sizeof(mControl));
	}

	static ResultType Destroy(GuiType &gui);
	static void DestroyIconsIfUnused(HICON ahIcon, HICON ahIconSmall); // L17: Renamed function and added parameter to also handle the window's small icon.
	ResultType Create();
	void AddRef();
	void Release();
	void SetLabels(LPTSTR aLabelPrefix);
	static void UpdateMenuBars(HMENU aMenu);
	ResultType AddControl(GuiControls aControlType, LPTSTR aOptions, LPTSTR aText);

	ResultType ParseOptions(LPTSTR aOptions, bool &aSetLastFoundWindow, ToggleValueType &aOwnDialogs, Var *&aHwndVar);
	void GetNonClientArea(LONG &aWidth, LONG &aHeight);
	void GetTotalWidthAndHeight(LONG &aWidth, LONG &aHeight);

	ResultType ControlParseOptions(LPTSTR aOptions, GuiControlOptionsType &aOpt, GuiControlType &aControl
		, GuiIndexType aControlIndex = -1); // aControlIndex is not needed upon control creation.
	void ControlInitOptions(GuiControlOptionsType &aOpt, GuiControlType &aControl);
	void ControlAddContents(GuiControlType &aControl, LPTSTR aContent, int aChoice, GuiControlOptionsType *aOpt = NULL);
	ResultType Show(LPTSTR aOptions, LPTSTR aTitle);
	ResultType Clear();
	ResultType Cancel();
	ResultType Close(); // Due to SC_CLOSE, etc.
	ResultType Escape(); // Similar to close, except typically called when the user presses ESCAPE.
	ResultType Submit(bool aHideIt);
	ResultType ControlGetContents(Var &aOutputVar, GuiControlType &aControl, LPTSTR aMode = _T(""));

	static VarSizeType ControlGetName(GuiType *aGuiWindow, GuiIndexType aControlIndex, LPTSTR aBuf);
	
	static GuiType *FindGui(LPTSTR aName);
	static GuiType *FindGui(HWND aHwnd);
	static GuiType *FindGuiParent(HWND aHwnd);

	static GuiType *ValidGui(GuiType *&aGuiRef); // Updates aGuiRef if it points to a destroyed Gui.

	GuiIndexType FindControl(LPTSTR aControlID);
	GuiControlType *FindControl(HWND aHwnd, bool aRetrieveIndexInstead = false)
	{
		GuiIndexType index = GUI_HWND_TO_INDEX(aHwnd); // Retrieves a small negative on failure, which will be out of bounds when converted to unsigned.
		if (index >= mControlCount) // Not found yet; try again with parent.
		{
			// Since ComboBoxes (and possibly other future control types) have children, try looking
			// up aHwnd's parent to see if its a known control of this dialog.  Some callers rely on us making
			// this extra effort:
			if (aHwnd = GetParent(aHwnd)) // Note that a ComboBox's drop-list (class ComboLBox) is apparently a direct child of the desktop, so this won't help us in that case.
				index = GUI_HWND_TO_INDEX(aHwnd); // Retrieves a small negative on failure, which will be out of bounds when converted to unsigned.
		}
		if (index < mControlCount && mControl[index].hwnd == aHwnd) // A match was found.  Fix for v1.1.09.03: Confirm it is actually one of our controls.
			return aRetrieveIndexInstead ? (GuiControlType *)(size_t)index : mControl + index;
		else // No match, so indicate failure.
			return aRetrieveIndexInstead ? (GuiControlType *)NO_CONTROL_INDEX : NULL;
	}
	int FindGroup(GuiIndexType aControlIndex, GuiIndexType &aGroupStart, GuiIndexType &aGroupEnd);

	ResultType SetCurrentFont(LPTSTR aOptions, LPTSTR aFontName);
	static int FindOrCreateFont(LPTSTR aOptions = _T(""), LPTSTR aFontName = _T(""), FontType *aFoundationFont = NULL
		, COLORREF *aColor = NULL);
	static int FindFont(FontType &aFont);

	void Event(GuiIndexType aControlIndex, UINT aNotifyCode, USHORT aGuiEvent = GUI_EVENT_NONE, UINT_PTR aEventInfo = 0);
	int CustomCtrlWmNotify(GuiIndexType aControlIndex, LPNMHDR aNmHdr);

	static WORD TextToHotkey(LPTSTR aText);
	static LPTSTR HotkeyToText(WORD aHotkey, LPTSTR aBuf);
	void ControlCheckRadioButton(GuiControlType &aControl, GuiIndexType aControlIndex, WPARAM aCheckType);
	void ControlSetUpDownOptions(GuiControlType &aControl, GuiControlOptionsType &aOpt);
	int ControlGetDefaultSliderThickness(DWORD aStyle, int aThumbThickness);
	void ControlSetSliderOptions(GuiControlType &aControl, GuiControlOptionsType &aOpt);
	int ControlInvertSliderIfNeeded(GuiControlType &aControl, int aPosition);
	void ControlSetListViewOptions(GuiControlType &aControl, GuiControlOptionsType &aOpt);
	void ControlSetTreeViewOptions(GuiControlType &aControl, GuiControlOptionsType &aOpt);
	void ControlSetProgressOptions(GuiControlType &aControl, GuiControlOptionsType &aOpt, DWORD aStyle);
	bool ControlOverrideBkColor(GuiControlType &aControl);

	void ControlUpdateCurrentTab(GuiControlType &aTabControl, bool aFocusFirstControl);
	GuiControlType *FindTabControl(TabControlIndexType aTabControlIndex);
	int FindTabIndexByName(GuiControlType &aTabControl, LPTSTR aName, bool aExactMatch = false);
	int GetControlCountOnTabPage(TabControlIndexType aTabControlIndex, TabIndexType aTabIndex);
	POINT GetPositionOfTabClientArea(GuiControlType &aTabControl);
	ResultType SelectAdjacentTab(GuiControlType &aTabControl, bool aMoveToRight, bool aFocusFirstControl
		, bool aWrapAround);
	void ControlGetPosOfFocusedItem(GuiControlType &aControl, POINT &aPoint);
	static void LV_Sort(GuiControlType &aControl, int aColumnIndex, bool aSortOnlyIfEnabled, TCHAR aForceDirection = '\0');
	static DWORD ControlGetListViewMode(HWND aWnd);
	static IObject *ControlGetActiveX(HWND aWnd);
	
	void UpdateAccelerators(UserMenu &aMenu);
	void UpdateAccelerators(UserMenu &aMenu, LPACCEL aAccel, int &aAccelCount);
	void RemoveAccelerators();
	static bool ConvertAccelerator(LPTSTR aString, ACCEL &aAccel);

	// See DPIScale() and DPIUnscale() for more details.
	int Scale(int x) { return mUsesDPIScaling ? DPIScale(x) : x; }
	int Unscale(int x) { return mUsesDPIScaling ? DPIUnscale(x) : x; }
};
