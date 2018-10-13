// win32hlp.h: Single file version
// DeadFish Shitware
// BuildDate: 10/05/18 00:25:16

#ifndef _WIN32_HLP_H_
#define _WIN32_HLP_H_
#include <stdshit.h>
#include <windowsx.h>
#define GET_WND_CONTEXT(type) \
	type* This = (type*)GetWindowLongPtr(hwnd, GWL_USERDATA);
#define INIT_DLG_CONTEXT(type, func) \
	if(uMsg == WM_INITDIALOG) { \
		SetWindowLongPtr(hwnd, DWL_USER, lParam); \
		type* This = (type*)lParam; func; return TRUE; } \
	type* This = (type*)GetWindowLongPtr(hwnd, DWL_USER); \
	if(This == NULL) return FALSE;
#define MEMBER_WNDPROC2(type, name) \
	ALWAYS_INLINE LRESULT name(HWND hwnd, UINT uMsg, WPARAM w, LPARAM lParam); \
	static LRESULT CALLBACK c##name(HWND hwnd, UINT uMsg, WPARAM w, LPARAM lParam) { \
		GET_WND_CONTEXT(type); return This->name(hwnd, uMsg, w, lParam); }
#define MEMBER_DLGPROC(type, name, func) \
	ALWAYS_INLINE INT_PTR name(HWND hwnd, UINT uMsg, WPARAM w, LPARAM lParam); \
	static INT_PTR CALLBACK c##name(HWND hwnd, UINT uMsg, WPARAM w, LPARAM lParam) { \
		INIT_DLG_CONTEXT(type, func); return This->name(hwnd, uMsg, w, lParam); }
#define MEMBER_DLGPROC2(t, n) MEMBER_DLGPROC(t,n, This->MACRO_CAT(n,Init)(hwnd))
#define DLGMSG_SWITCH(cse, def) { LONG_PTR msgResult = 0; HWND& sender = *(HWND*)&lParam; \
	switch(uMsg) { cse; default: switch(uMsg) { def; default: return FALSE; }} \
	if(msgResult) { SetWindowLongPtr(hwnd, DWL_MSGRESULT, msgResult); } return TRUE; }
#define WNDMSG_SWITCH(cse, def) { LONG_PTR msgResult = 0; HWND& sender = *(HWND*)&lParam; \
	switch(uMsg) { cse; default: switch(uMsg) { def; default: return DefWindowProc( \
		hwnd, uMsg, wParam, lParam); }} return msgResult; }
#define CASE_COMMAND(cse, def) case WM_COMMAND: { HWND& sender = *(HWND*)&lParam; \
	switch(wParam) { cse; default: switch(uMsg) { def; default: break; }}} break;
#define CASE_NOTIFY(cse, def) case WM_NOTIFY: { NMHDR& hdr = *(NMHDR*)lParam; switch( \
	hdr.idFrom | (hdr.code<<16)) { cse; default: switch(uMsg) { def; default: break; }}} break;
#define ON_MESSAGE(msg, f) case msg: { f; break; }
#define ON_MSGRNG(m1, m2, f) case m1 ... m2: { f; break; }
#define OM_MOUSEMSG(f) ON_MSGRNG(WM_MOUSEFIRST, WM_MOUSELAST, f)
#define CASE_XY(x, y) case MAKELPARAM(y, x):
#define ON_CONTROL(nc, id, f) case MAKELPARAM(id, nc): { f; break; }
#define ON_COMMAND(id, f) ON_CONTROL(0, id, f)
#define ON_NOTIFY(nc, id, f) ON_CONTROL(nc, id, f)
#define ON_CONTROL_RANGE(nc, id, id2, f) case MAKELPARAM(id, nc) ... MAKELPARAM(id2, nc): \
	{ int index = LOWORD(wParam)-id; f; break; }
#define ON_NOTIFY_RANGE(nc, id, id2, f) case MAKELPARAM(id, nc) ... MAKELPARAM(id2, nc): \
	{ int index = hdr.idFrom -id; f; break; }
#define ON_COMMAND_RANGE(id, id2, f) ON_CONTROL_RANGE(0, id, id2, f)
#define ON_RADIO_RNG(id, id2, f) ON_COMMAND_RANGE(id, id2, \
	if(IsButtonChecked((HWND)lParam)) f; )
#define ON_MESSAGE0(msg, f) case msg: { f; return 0; }
#define ON_CTLCOLORSTATIC(f) ON_MESSAGE0(WM_CTLCOLORSTATIC,f)
#define ON_CTLCOLOREDIT(f) ON_MESSAGE0(WM_CTLCOLOREDIT,f)
#define ON_CTLCOLORBTN(f) ON_MESSAGE0(WM_CTLCOLORBTN,f)
#define ON_LVN_NOTIFY(nc, id, f) ON_NOTIFY(nc, id, \
	NMLISTVIEW& nmv = *(LPNMLISTVIEW)lParam; f)
#define ON_LVN_ITEMACT(nc, id, f) ON_NOTIFY(nc, id, \
	NMITEMACTIVATE& nmv = *(LPNMITEMACTIVATE)lParam; f)
#define ON_LVN_KEYDOWN(id, f) ON_NOTIFY(LVN_KEYDOWN, id, \
	NMLVKEYDOWN& nmv = *(LPNMLVKEYDOWN)lParam; f)
#define ON_LVN_STATECHG(id, f) ON_LVN_NOTIFY(LVN_ITEMCHANGED, id, \
	if(nmv.uChanged & LVIF_STATE) { f; } )
#include <olectl.h>
#define REFLECT_DRAWITEM ON_MESSAGE(WM_DRAWITEM, drawItemReflect(lParam))
static void drawItemReflect(LPARAM lParam){
LPDRAWITEMSTRUCT lpDIS=(LPDRAWITEMSTRUCT)lParam;
SendMessageW(lpDIS->hwndItem,OCM_DRAWITEM,0,lParam);}
LRESULT WINAPI sendMessage(HWND,UINT);
LRESULT WINAPI sendMessage(HWND,UINT,WPARAM);
LRESULT WINAPI sendMessageL(HWND,UINT,LPARAM);
LRESULT WINAPI sendDlgMsg(HWND,DWORD,UINT);
LRESULT WINAPI sendDlgMsg(HWND,DWORD,UINT,WPARAM);
LRESULT WINAPI sendDlgMsgL(HWND,DWORD,UINT,LPARAM);
static inline LRESULT sendMessage(HWND h,UINT m,
WPARAM w,LPARAM l){return SendMessageW(h,m,w,l);}
static inline LRESULT WINAPI sendDlgMsg(HWND h,DWORD c,UINT m,
WPARAM w,LPARAM l){return SendDlgItemMessageW(h,c,m,w,l);}
LRESULT WINAPI sendMessageU(HWND,UINT,cch*str);
LRESULT WINAPI sendMessageU(HWND,UINT,WPARAM,cch*);
LRESULT WINAPI sendDlgMsgU(HWND,DWORD,UINT,cch*str);
LRESULT WINAPI sendDlgMsgU(HWND,DWORD,UINT,WPARAM,cch*);
cstr WINAPI getWndTextIdx(HWND h,DWORD m,DWORD i);
cstr WINAPI getDlgTextIdx(HWND h,DWORD c,DWORD m,DWORD i);
#define RECT_XY(rc) (rc).left, (rc).top
#define RECT_WH(rc) (rc).right-(rc).left, (rc).bottom-(rc).top
#define RECT_LTRB(rc) RECT_XY(rc), (rc).right, (rc).bottom
#define RECT_XYWH(rc)  RECT_XY(rc), RECT_WH(rc)
#define XYWH_LTRB(rc) (rc).x, (rc).y, XYWH_R(rc), XYWH_B(rc)
static LONG RECT_W(RECT&rc){return rc.right-rc.left;}
static LONG RECT_H(RECT&rc){return rc.bottom-rc.top;}
static void setSize(RECT*rc,int width,int height){
rc->right=rc->left+width;rc->bottom=rc->top+height;}
bool WINAPI RectInRect(const RECT*big,const RECT*Small);
static POINT lParamToPnt(LPARAM lParam){return POINT{
GET_X_LPARAM(lParam),GET_Y_LPARAM(lParam)};}
struct XYWH{LONG x,y,w,h;};
static LONG XYWH_R(XYWH&rc){return rc.x+rc.w;}
static LONG XYWH_B(XYWH&rc){return rc.y+rc.h;}
RECT WINAPI GetChildRect(HWND hWnd);RECT WINAPI GetChildRect(HWND hWnd,UINT ctrlId);
XYWH WINAPI GetChildXywh(HWND hWnd);XYWH WINAPI GetChildXywh(HWND hWnd,UINT ctrlId);
RECT WINAPI MurderChild(HWND hWnd,UINT ctrlId);
HWND WINAPI PossessChild(HWND hwnd,UINT ctrlId,WNDPROC wndProc,void*This);
HWND WINAPI PossessWindow(HWND hwnd,WNDPROC wndProc,void*This);
void WINAPI EnableDlgItem(HWND hwnd,UINT ctrlId,BOOL bEnable);
void WINAPI EnableDlgItems(HWND hwnd,const WORD*dlgItems,int itemCount,BOOL bEnable);
void WINAPI ShowDlgItems(HWND hwnd,const WORD*dlgItems,int itemCount,BOOL bShow);
BOOL WINAPI IsButtonChecked(HWND hButton);
void WINAPI dlgCombo_addStrs(HWND,DWORD,cch*const*,int);
int WINAPI dlgCombo_addStr(HWND,DWORD,cch*);
int WINAPI dlgCombo_addStr(HWND,DWORD,cch*,LPARAM);
int WINAPI dlgCombo_setData(HWND,DWORD,int,LPARAM);
LPARAM WINAPI dlgCombo_getData(HWND,DWORD,int);
int WINAPI dlgCombo_getSel(HWND,DWORD);
int WINAPI dlgCombo_setSel(HWND,DWORD,int);
int WINAPI dlgCombo_reset(HWND,DWORD);
cstr WINAPI dlgCombo_getText(HWND,DWORD,int);
int WINAPI dlgCombo_find(HWND,DWORD,cch*);
int WINAPI dlgCombo_selStr(HWND,DWORD,cch*);
LPARAM WINAPI dlgCombo_getData2(HWND h,DWORD c,int i);
int WINAPI dlgCombo_findData(HWND h,DWORD c,LPARAM d);
void WINAPI CheckDlgRadio(HWND hDlg,int nIDButton);
int WINAPI GetDlgRadioCheck(HWND hDlg,int first,int last);
void WINAPI addDlgTabPage(HWND hwnd,UINT ctrlId,int index,LPCSTR tabName);
void WINAPI renameDlgTabPage(HWND hwnd,UINT ctrlId,int index,LPCSTR tabName);
void WINAPI addDlgTabPage(HWND hwnd,UINT ctrlId,int index,LPCWSTR tabName);
void WINAPI renameDlgTabPage(HWND hwnd,UINT ctrlId,int index,LPCWSTR tabName);
void WINAPI removeDlgTabPage(HWND hwnd,UINT ctrlId,int index);
void WINAPI resetDlgTabCtrl(HWND hwnd,UINT ctrlId);
int WINAPI setDlgTabPage(HWND hwnd,UINT ctrlID,int page);
int WINAPI getDlgTabPage(HWND hwnd,UINT ctrlID);
UINT WINAPI setDlgSpinRange(HWND hwnd,UINT ctrlID,UINT min,UINT max);
void WINAPI setDlgSpinValue(HWND hwnd,UINT ctrlId,UINT value);
UINT WINAPI getDlgSpinValue(HWND hwnd,UINT ctrlId);
UINT WINAPI validateDlgSpin(HWND hwnd,UINT ctrlId);
HWND WINAPI setDlgSpinValue(HWND hwnd,UINT ctrlId,
UINT min,UINT max,UINT value);
void WINAPI setDlgSpinInc(HWND hwnd,UINT increment);
HWND msgWnd_create(WNDPROC wndProc,LPVOID userData,LPVOID createParams);
HWND stdClass_create(LPCTSTR lpWindowName,DWORD dwStyle,DWORD dwExStyle,HWND hWndParent,
HMENU hMenu,WNDPROC wndProc,LPVOID userData=0,LPVOID createParams=0);
HWND stdClass_create(LPCTSTR lpWindowName,DWORD dwStyle,DWORD dwExStyle,
int X,int Y,int nWidth,int nHeight,HWND hWndParent,HMENU hMenu,
WNDPROC wndProc,LPVOID userData=0,LPVOID createParams=0);
void WINAPI lstView_insColumn(HWND hList,int index,int width,const char*name);
#define _LSTVW_F1_(CT, LT) \
int WINAPI lstView_iosText(HWND hList, int item, const CT* text, int iSub, LT* lvi, int mask); \
int WINAPI lstView_iosText(HWND hList, int item, const CT* text); \
int WINAPI lstView_iosText(HWND hList, int item, const CT* text, LPARAM data); \
int WINAPI lstView_iosText(HWND hList, int item, const CT* text, LPARAM data, int img); \
int WINAPI lstView_iosText(HWND hList, int item, int iSub, const CT* text);
_LSTVW_F1_(char,LVITEMA);_LSTVW_F1_(WCHAR,LVITEMW);
void WINAPI lstView_iosInt(HWND hList,int item,int subItem,int val);
void WINAPI lstView_iosInt(HWND hList,int item,int subItem,int val,LPARAM data);
void WINAPI lstView_setData(HWND hList,int item,LPARAM data);
bool WINAPI lstView_getItem(HWND hList,int item,int subItem,LVITEMW*lvi);
LPARAM WINAPI lstView_getText(HWND hList,int item,int subItem,WCHAR*text,int max);
LPARAM WINAPI lstView_getData(HWND hList,int item);
int WINAPI listView_getCurSel(HWND hList);
void WINAPI listView_setCurSel(HWND hList,int item);
int WINAPI listView_getSel(HWND hList,int item);
int WINAPI listView_nextSel(HWND hList,int iStart);
void WINAPI listView_setSel(HWND hList,int item,BOOL bSelect);
int WINAPI listView_getFocus(HWND hList);
void WINAPI listView_setFocus(HWND hList,int item);
#define lstView_insText(a,b,c) lstView_iosText(a,(b)|0x80000000,0,c)
#define lstView_insTxtDat(a,b,c,d) lstView_iosText(a,(b)|0x80000000,0,c,d)
#define lstView_insInt(a,b,c) lstView_iosInt(a,(b)|0x80000000,0,c)
#define lstView_insIntDat(a,b,c,d) lstView_iosInt(a,(b)|0x80000000,0,c,d)
int WINAPI simpleMsgLoop(void);
int WINAPI dialogMsgLoop(void);
int WINAPI dialogMsgPeek(void);
int WINAPI listBox_addStr(HWND,DWORD,cch*);
int WINAPI listBox_addStr(HWND,DWORD,cch*,LPARAM);
int WINAPI listBox_setData(HWND,DWORD,int,LPARAM);
LPARAM WINAPI listBox_getData(HWND,DWORD,int item);
int WINAPI listBox_getCurSel(HWND,DWORD);
int WINAPI listBox_setCurSel(HWND,DWORD,int);
int WINAPI listBox_getSel(HWND,DWORD,int);
int WINAPI listBox_setSel(HWND,DWORD,int,int);
int WINAPI listBox_selCount(HWND,DWORD);
int WINAPI listBox_reset(HWND,DWORD);
cstr WINAPI listBox_getText(HWND,DWORD,int);
int WINAPI listBox_find(HWND,DWORD,cch*);
int WINAPI listBox_selStr(HWND,DWORD,cch*);
xarray<int>WINAPI listBox_selItems(HWND,DWORD);
char*WINAPI inputBox(HWND hwnd,cch*title,
cch*prompt,cch*content);
xarray<xstr>WINAPI hDropGet(HANDLE hDrop);
xarray<wxstr>WINAPI hDropGetW(HANDLE hDrop);
void __thiscall dynOpenFileDlg_free(OPENFILENAMEA*ofn);
struct OpenFileName_:OPENFILENAMEA{
~OpenFileName_(){dynOpenFileDlg_free(this);}
cstr&cStr(){return*(cstr*)&lpstrFile;}
xarray<xstr>&lst(){return*(xarray<xstr>*)&lpstrFile;}};
struct OpenFileName:OpenFileName_{OpenFileName();BOOL doModal(HWND hParent);};
struct SaveFileName:OpenFileName_{SaveFileName();BOOL doModal(HWND hParent);};
WCHAR*selectFolderW(HWND hParent,const WCHAR*title,const WCHAR*initDir);
WCHAR*selectFilesW(HWND hParent,const WCHAR*title,const WCHAR*initDir);
cstr selectFolder(HWND hParent,cch*title,cch*initDir);
xarray<cch*>selectFiles(HWND hParent,cch*title,cch*initDir);
#endif