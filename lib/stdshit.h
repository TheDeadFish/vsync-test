// stdshit.h: Single file version
// DeadFish Shitware 2013-2014
// BuildDate: 09/14/18 04:24:20
#ifndef _STDSHIT_H_
#define _STDSHIT_H_
#include <tchar.h>
#include <stdio.h>
#include <windows.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdarg.h>
#include <errno.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>
#define MCAT2(name, ...) name##__VA_ARGS__
#define MCAT(name, ...) MCAT2(name, __VA_ARGS__)
#define EXTRACT(...) EXTRACT __VA_ARGS__
#define NOTHING_EXTRACT
#define UNPAREN(x) MCAT(NOTHING_, EXTRACT x)
#define MSTR(x) #x
#define VA_NARGS_IMPL(_1, _2, _3, _4, _5, N, ...) N
#define VA_NARGS(...) VA_NARGS_IMPL(X,##__VA_ARGS__, 4, 3, 2, 1, 0)
#define VARARG_IMPL2(base, count, ...) base##count(__VA_ARGS__)
#define VARARG_IMPL(base, count, ...) VARARG_IMPL2(base, count, __VA_ARGS__)
#define VARARG(base, ...) VARARG_IMPL(base, VA_NARGS(__VA_ARGS__), __VA_ARGS__)
#define _MIF_0(a, b) UNPAREN(b)
#define _MIF_1(a, b) UNPAREN(a)
#define MIF(c,a,b) MCAT(_MIF_, c)(a,b)
#define M_EVAL(...) MEVALA(__VA_ARGS__)
#define MEVALA(...) MEVAL9(MEVAL9(__VA_ARGS__))
#define MEVAL9(...) MEVAL8(MEVAL8(__VA_ARGS__))
#define MEVAL8(...) MEVAL7(MEVAL7(__VA_ARGS__))
#define MEVAL7(...) MEVAL6(MEVAL6(__VA_ARGS__))
#define MEVAL6(...) MEVAL5(MEVAL5(__VA_ARGS__))
#define MEVAL5(...) MEVAL4(MEVAL4(__VA_ARGS__))
#define MEVAL4(...) MEVAL3(MEVAL3(__VA_ARGS__))
#define MEVAL3(...) MEVAL2(MEVAL2(__VA_ARGS__))
#define MEVAL2(...) MEVAL1(MEVAL1(__VA_ARGS__))
#define MEVAL1(...) MEVAL0(MEVAL0(__VA_ARGS__))
#define MEVAL0(...) __VA_ARGS__
#define M_EMT()
#define M_DEFER1(id) id M_EMT()
#define M_DEFER2(id) id M_EMT M_EMT()()
template<class T,class U>
union _CAST_{T src;U dst;};
#define CAST(type, x) (((_CAST_<typeof(x), type>*)&(x))->dst)
#define PCST(type, x) (((_CAST_<typeof(*x), type>*)(x))->dst)
#define GLOB_LAB(name) ".globl " name "; " name ":"
#define ASM_LOCAL(name, ...) asm(".section .text$" \
name ";" name ":" __VA_ARGS__);
#define ASM_FUNC(name, ...) asm(".section .text$" \
name ";" GLOB_LAB(name) __VA_ARGS__);
#define REF_SYMBOL(symb) asm(".def _"#symb";.scl 2;.type 32;.endef");
#define DEF_SECTDAT(name) __attribute__((section(".text$"MSTR(name))))
#define DEF_RDTEXT(n, t) DEF_SECTDAT(n) static const char n[] = t;
#define DEF_RDTEXTW(n, t) DEF_SECTDAT(n) static const WCHAR n[] = L##t;
#define AMIF(n,t,f) ".if "#n";" t ";.else;" f ";.endif;"
#define ALWAYS_INLINE __inline__ __attribute__((always_inline))
#define NEVER_INLINE __attribute__ ((noinline))
#define NORETURN __attribute__((noreturn))
#define UNREACH __builtin_unreachable()
#define FATALFUNC __attribute__((noreturn,cold))
#define NOTHROW __attribute__((__nothrow__))
#define getReturn() __builtin_return_address(0)
#define TLS_VAR __thread
#define TLS_EXTERN extern __thread
#define INITIALIZER(f) \
__attribute__((constructor)) void f(void)
#define REGCALL(x) __attribute__((stdcall,regparm(x)))
#define SHITCALL2 __fastcall
#define SHITCALL __stdcall
#define SHITSTATIC __stdcall static
#define likely(x) __builtin_expect((x),1)
#define unlikely(x) __builtin_expect((x),0)
#define ARGFIX(arg) asm("" : "+m"(arg));
#define VARFIX(var) asm("" : "+g"(var));
#define VALFIX(v)({auto r = v; VARFIX(r); r;})
#define VOIDPROC(proc) Void((void*)&proc)
#define PACK1(...) _Pragma("pack(push, 1)") __VA_ARGS__ _Pragma("pack(pop)")
#define TMPL(t) template <class t>
#define TMPL2(t,u) template <class t, class u>
#define _MCSE(arg) case arg:
#define MCSE(...) MAP(_MCSE, __VA_ARGS__)
#define HOTCALL(ftype, addr) (*((typeof(&ftype))(size_t(addr))))
#define __assume(cond) do { if (!(cond)) __builtin_unreachable(); } while (0)
#define ZINIT memset(this, 0, sizeof(*this));
#define ei else if
#define NULL_CHECK(ptr) ({bool nck_; asm("test %1,%1" \
: "=@ccz"(nck_) : "r"(ptr)); nck_;})
#define THIS_NULL_CHECK() if(NULL_CHECK(this)) return 0;
#define ALIGN4(arg) ALIGN(arg, 3)
#define ALIGN_PAGE(arg) ALIGN(arg, 4095)
static inline size_t ALIGN(size_t arg,size_t bound)
{return((arg+bound)&~bound);}
TMPL(T)T*notNull(T*p){__assume(p);return p;}
#define IFRET(...) if(auto result = __VA_ARGS__) return result;
#define PTRADD(ptr, offset) (ptr = Void(ptr)+(offset))
#define PTRDIFF(ptr1, ptr2) (size_t(ptr1)-size_t(ptr2))
#define offsetof1(st, m) ((size_t)(&((st *)0)->m))
#define endsetof(st, m) ((size_t)((&((st *)0)->m)+1))
#define rangeof(st, m1, m2) (endsetof(st,m2)-offsetof(st,m1))
#define RangeOf(m1,m2) (size_t((&m2)+1)-size_t(&m1))
#define RANGE_ARG(m1, m2) (byte*)&m1, RangeOf(m1,m2)
#define RANGE2_ARG(src, m1, m2) (byte*)&m1, src, RangeOf(m1,m2)
#define RANGE_ARGX(m1, m2) &m1, RangeOf(m1,m2)
#define RANGE2_ARGX(src, m1, m2) &m1, src, RangeOf(m1,m2)
#define TMPNAME(name) MCAT(name,__LINE__)
#define DEF_BEGINEND(type, ptr, len) \
type* begin(size_t ofs=0) { return ((type*)ptr)+ofs; } \
type* end(size_t ofs=0) { return ((type*)(ptr+len))+ofs; } \
operator type*() { return ptr; }
#define DEF_RETPAIR_(n1,n2,T,a,U,b,x,y) struct n1{union{T a;T m1;};union \
{U b;U m2;};n2(){}n2(T ai){a=ai;} n2(T ai,U bi){a=ai;b=bi;} \
operator T&(){return a;}x operator->(){return y;}};
#define DEF_RETPAIR(n,T,a,U,b) DEF_RETPAIR_(n,n,T,a,U,b,T,a)
#define DEF_RETPAIR2(n,T,a,U,b) DEF_RETPAIR_(n,n,T,a,U,b,U,b)
#define DEF_RETPAIR3(n,n2,T,a,U,b) DEF_RETPAIR_(n,n2,T,a,U,b,U,b)
#define GET_RETPAIR2(var1, var2, call) auto TMPNAME(RPTmp)=call; \
var1 TMPNAME(RPTmp).m1;var2 TMPNAME(RPTmp).m2;
#define GET_RETPAIR(var1, var2, call) GET_RETPAIR2(var1=, var2=, call)
TMPL(T)struct RetEdx{int eax;T edx;RetEdx(int var)
{asm("":"=a"(eax));edx=var;}operator T&(){return edx;}};
TMPL(T)bool _BTST(T&var,int bit){return var&(1<<bit);}
TMPL(T)bool _BSET(T&var,int bit){
bool result=_BTST(var,bit);var|=(1<<bit);return result;}
TMPL(T)bool _BCLR(T&var,int bit){
bool result=_BTST(var,bit);var&=~(1<<bit);return result;}
typedef unsigned char byte;
typedef unsigned short word;
typedef unsigned int uint;
typedef unsigned int u32;
typedef signed int s32;
typedef unsigned char u8;
typedef signed char s8;
typedef unsigned short u16;
typedef signed short s16;
typedef unsigned long long u64_;
typedef signed long long s64_;
typedef u64_ __attribute__((aligned(4)))u64;
typedef s64_ __attribute__((aligned(4)))s64;
typedef u64_ __attribute__((aligned(4)))u64p4;
typedef s64_ __attribute__((aligned(4)))s64p4;
static inline INT32 iDiv6432(INT64 num,INT32 dom){UINT32 result;
asm("idivl %2":"=a"(result):"A"(num),"rm"(dom));return result;}
static inline UINT32 uDiv6432(UINT64 num,UINT32 dom){UINT32 result;
asm("divl %2":"=a"(result):"A"(num),"rm"(dom));return result;}
TMPL2(T,U=T)ALWAYS_INLINE T release(T&ptr,U newPtr=0){
T tmpPtr=ptr;ptr=newPtr;return tmpPtr;}
TMPL2(T,U=T)ALWAYS_INLINE T replace(T&ptr,U newPtr){
free(ptr);return ptr=newPtr;}
#define free_repl(ptr, newPtr) (::free(ptr), ptr = newPtr)
#define ADDP(ptr, len) asm volatile(".if %c1 == 1;inc %0;.elseif %c1 == -1;" \
"dec %0;.else;lea %c1(%0),%0;.endif" : "+r"(ptr) : "e"(len));
#define INCP(ptr) ADDP(ptr, sizeof(*ptr))
#define WRI(ptr, data) ({ VARFIX(ptr); *ptr = data; INCP(ptr); })
#define RDI(ptr) ({ RDI2(ptr, auto ret); ret;})
#define RDI2(ptr, data) VARFIX(ptr); data = *ptr; INCP(ptr);
#define swapReg(x, y) asm("XCHG %0, %1" : "+r"(x), "+r"(y));
#define DEF_PX(n,T) TMPL(Z) T*& MCAT(P,n)(const Z& p) { return CAST(T*, p); } \
TMPL(Z) T& MCAT(R,n)(Z p, size_t o=0,size_t n=0) { return ((T*)(PB(p)+o))[n]; } \
TMPL(Z) T* MCAT(P,n)(Z p, size_t o,size_t n=0) { return &MCAT(R,n)(PB(p), o, n); }
DEF_PX(B,BYTE)DEF_PX(C,CHAR)DEF_PX(S,INT16)DEF_PX(W,WORD)
DEF_PX(I,INT32)DEF_PX(U,DWORD)DEF_PX(L,INT64)DEF_PX(Q,UINT64)
DEF_PX(T,SIZE_T)DEF_PX(R,SSIZE_T)DEF_PX(F,float)DEF_PX(D,double)
TMPL(T)struct VaArgFwd{T*pfmt;va_list
start(){return(va_list)(PT(pfmt)+1);}};
#define VA_ARG_FWD(fmt) VaArgFwd< \
decltype (fmt)> va = {&fmt};
#define pNew(ptr, ...) ({ new(notNull(ptr)) typeof(*(ptr)){__VA_ARGS__}; })
#define rNew(ref, ...) (*pNew(&ref, __VA_ARGS__))
TMPL(T)void pDel(T*ptr){ptr->~T();}
#define hasDtorT(T) !std::is_trivially_destructible<T>::value
#define hasDtorp(p) hasDtorT(typeof(*p))
#define _ADDU_OVF_(dst, src) ({ bool _ovf_; asm("add %2, %1" \
: "=@ccc"(_ovf_), "+g"(dst) : "ri"(src)); _ovf_; })
#define _SUBU_OVF_(dst, src) ({ bool _ovf_; asm("sub %2, %1" \
: "=@ccc"(_ovf_), "+g"(dst) : "ri"(src)); _ovf_; })
#include <type_traits>
template<bool T,typename V>
using enable_if_t=typename std::enable_if<T,V>::type;
template<bool B,class T,class F>
using conditional_t=typename std::conditional<B,T,F>::type;
TMPL(T)
enable_if_t<!std::is_class<T>::value,bool>isNeg(const T&value)
{return(typename std::make_signed<T>::type)(value)<0;}
TMPL(T)T uns(T v){return(std::make_unsigned_t<T>)v;}
TMPL(T)T&unsR(T&v){return*(std::make_unsigned_t<T>*)&v;}
struct is_cstyle_castable_impl{
template<typename _From,typename _To,typename
=decltype((_To)(std::declval<_From>()))>
static std::true_type __test(int);
template<typename,typename>
static std::false_type __test(...);};
template<typename _From,typename _To>
struct is_cstyle_castable
:public std::integral_constant<bool,(decltype(
is_cstyle_castable_impl::__test<_From,_To>(0))::value)>{};
#include <tuple>
#define MakeDelegate(obj, func) \
decltype(Delegate_(obj, func))::Bind<func>(obj)
template<class R,class... P>
struct Delegate{
Delegate(){}Delegate(void*stub){stub_ptr=(stub_type)stub;}
Delegate(void*object,void*stub){
object_ptr=object;stub_ptr=(stub_type)stub;}
TMPL(T)
void set(T object,R(__thiscall*stub)(T,P... params))
{object_ptr=(void*)object;
stub_ptr=(stub_type)stub;}
TMPL(T)
void set(T*object,R(T::*stub)(P... params))
{object_ptr=(void*)object;
stub_ptr=(void*)(object_ptr->*stub);}
R operator()(P... params)const
{return(*stub_ptr)(object_ptr,params...);}
bool isValid(void)
{return(stub_ptr!=0);}
typedef R(__thiscall*stub_type)
(void*object_ptr,P... params);
void*object_ptr;
stub_type stub_ptr;};
template<class R,class... P>
struct MemberFunc{
MemberFunc(){}
MemberFunc(void*stub){stub_ptr=(stub_type)stub;}
R operator()(void*object_ptr,P... params)const
{return(*stub_ptr)(object_ptr,params...);}
bool isValid(void)
{return(stub_ptr!=0);}
typedef R(__thiscall*stub_type)
(void*object_ptr,P... params);
stub_type stub_ptr;};
#define DELEGATE_WCTX(nm, cv, ck) template <class T, class R, typename... P> struct nm {template \
<R (cv *TMethod)(T*, P...)> struct Bind { Bind(T* ctx) { object_ptr = (void*)ctx; } void* \
object_ptr; template <class RO, class... PO> static RO __thiscall stub(void* ctx, PO... params) {\
return TMethod((T*)ctx, params...); } template <class RO, class... PO> operator Delegate<RO, \
PO...>() { UNPAREN(ck); return Delegate<RO, PO...>(object_ptr, (void*)&stub<RO, PO...>); }};}; \
template <class T, class R, typename... P> nm<T, R, P...> Delegate_(T* obj, R (cv *TMethod)(T*, \
P... params)) { return nm<T, R, P...>(); }
DELEGATE_WCTX(Delegate_cdecl,,);DELEGATE_WCTX(Delegate_std,__stdcall,);
DELEGATE_WCTX(Delegate_this,__thiscall,(if(std::is_same
<std::tuple<P...>,std::tuple<PO...>>::value)return Delegate<RO,PO...>(0,(void*)TMethod);));
#define DELEGATE_WOCTX(nm, cv, ck) template <class R, typename... P> struct nm { template <R (cv \
*TMethod)(P...)> struct Bind { Bind(int dummy) {} template <class RO, class... PO> static RO \
__thiscall stub(void* ctx, PO... params) { return TMethod(params...); } template <class RO, \
class... PO> operator Delegate<RO, PO...>() { UNPAREN(ck); return Delegate<RO, PO...>((void*)0, \
(void*)&stub<RO, PO...>); }};}; template <class R, typename... P> nm<R, P...> Delegate_( \
int dummy, R (cv *TMethod)(P... params)) { return nm<R, P...>(); }
DELEGATE_WOCTX(Delegate_noctx,,)DELEGATE_WOCTX(Delegate_noctx2,__stdcall,(if(std::is_same
<std::tuple<P...>,std::tuple<PO...>>::value)return Delegate<RO,PO...>(0,(void*)TMethod);))
template<class S,class T,class R,typename... P>
struct Delegate_member{
template<R(T::*TMethod)(P...)>
struct Bind{
Bind(S*ctx){object_ptr=(void*)static_cast<T*>(ctx);}
void*object_ptr;
template<class RO,class... PO>
static RO __thiscall stub(void*ctx,PO... params)
{return(((T*)ctx)->*TMethod)(params...);}
template<class RO,class... PO>
operator Delegate<RO,PO...>(){
if(std::is_same<std::tuple<P...>,std::tuple<PO...>>::value)
return Delegate<RO,PO...>(object_ptr,
(void*)(((T*)object_ptr)->*TMethod));
return Delegate<RO,PO...>(
object_ptr,(void*)&stub<RO,PO...>);}
operator MemberFunc<R,P...>(){
Delegate<R,P...>delgate=*this;
return MemberFunc<R,P...>((void*)delgate.stub_ptr);}};};
template<class S,class T,class R,typename... P>Delegate_member<S,T,R,P...>Delegate_(
S*obj,R(T::*TMethod)(P... params)){return Delegate_member<S,T,R,P...>();}
template<typename T,typename U>
struct helper:helper<T,decltype(&U::operator())>{};
template<typename T,typename C,typename R,typename... A>
struct helper<T,R(C::*)(A...)const>{
static const bool value=std::is_convertible<T,R(*)(A...)>::value;};
template<typename T>struct is_stateless{
static const bool value=helper<T,T>::value;};
template<class F>
struct Delegate_lambda{const F&func;
Delegate_lambda(const F&func_):func(func_){}
template<class RO,class... PO>
static RO __thiscall stub(void*ctx,PO... params)
{return(*(F*)ctx)(params...);}
template<class RO,class... PO>
operator Delegate<RO,PO...>(){return Delegate<RO,PO...>(
is_stateless<F>::value?0:(void*)&func,(void*)&stub<RO,PO...>);}};
template<class F>
Delegate_lambda<F>MakeDlgtLmbd(const F&func)
{return Delegate_lambda<F>(func);}
template<class T,class F>
struct Delegate_lambda2{const F&func;T*obj;
Delegate_lambda2(T*obj_,const F&func_):obj(obj_),func(func_){}
template<class RO,class... PO>
static RO __thiscall stub(void*ctx,PO... params)
{return(*(F*)0)((T*)ctx,params...);}
template<class RO,class... PO>
operator Delegate<RO,PO...>(){return Delegate<RO,PO...>(
(void*)obj,(void*)&stub<RO,PO...>);}};
template<class T,class F>
Delegate_lambda2<T,F>MakeDlgtLmbd(T*obj,const F&func)
{return Delegate_lambda2<T,F>(obj,func);}
#define REGFIX(r, v) asm("" : "+"#r(v))
#define DEF_EAX(arg) register arg asm ("eax")
#define DEF_EBX(arg) register arg asm ("ebx")
#define DEF_ECX(arg) register arg asm ("ecx")
#define DEF_EDX(arg) register arg asm ("edx")
#define DEF_ESI(arg) register arg asm ("esi")
#define DEF_EDI(arg) register arg asm ("edi")
#define movzx(o,p,r) ({ \
if(sizeof(p) == 1) asm("movzbl %1, %0" : "="#r(o) : "m"(p)); \
ei(sizeof(p) == 2) asm("movzwl %1, %0" : "="#r(o) : "m"(p)); })
#define lodsx(ptr, ax) ({if(sizeof(ax) == 1) lodsb(ptr, ax); \
ei(sizeof(ax) == 2) lodsw(ptr, ax); else lodsl(ptr, ax);})
#define lodsb(ptr, ax) ({ asm ("lodsb" :"=a"(ax), "=S"(ptr) : "S"(ptr)); })
#define lodsw(ptr, ax) ({ asm ("lodsw" :"=a"(ax), "=S"(ptr) : "S"(ptr)); })
#define lodsl(ptr, ax) ({ asm ("lodsl" :"=a"(ax), "=S"(ptr) : "S"(ptr)); })
#define stosx(ptr, ax) ({if(sizeof(ax) == 1) stosb(ptr, ax); \
ei(sizeof(ax) == 2) stosw(ptr, ax); else stosl(ptr, ax);})
#define stosb(ptr, ax) ({ asm volatile ("stosb" : "=D"(ptr) : "D"(ptr), "a"(ax)); })
#define stosw(ptr, ax) ({ asm volatile ("stosw" : "=D"(ptr) : "D"(ptr), "a"(ax)); })
#define stosl(ptr, ax) ({ asm volatile ("stosl" : "=D"(ptr) : "D"(ptr), "a"(ax)); })
#define incml(ptr) ({ \
asm ("incl %0" :"=m"(ptr) : "m"(ptr)); })
#define movfx(reg, data) ({ typeof(data) _x86bits_ = data; \
asm volatile ("" :: #reg(_x86bits_)); _x86bits_; })
#define movbx2(dest, data, d, s) ({ asm ("movb %b2, %b0" \
: "="#d(dest) : "0"(dest), #s(data)); })
#define movwx2(dest, data, d, s) ({ asm ("movw %w2, %w0" \
: "="#d(dest) : "0"(dest), #s(data)); })
#define movlx2(dest, data, d, s) ({ asm ("movl %k2, %k0" \
: "="#d(dest) : "0"(dest), #s(data)); })
#define movb2(dest, data) movbx2(dest, data, r, g)
#define movw2(dest, data) movwx2(dest, data, r, g)
#define movl2(dest, data) movlx2(dest, data, r, g)
#define movrb2(reg, dest, data) movbx2(dest, data, reg, g)
#define movrw2(reg, dest, data) movwx2(dest, data, reg, g)
#define movrl2(reg, dest, data) movlx2(dest, data, reg, g)
#define movbx(data, d, s) ({ typeof(data) _x86bits_; \
asm ("movb %b1, %b0" : "="#d(_x86bits_) : #s(data)); _x86bits_; })
#define movwx(data, d, s)({ typeof(data) _x86bits_; \
asm ("movw %w1, %w0" : "="#d(_x86bits_) : #s(data)); _x86bits_; })
#define movlx(data, d, s) ({ typeof(data) _x86bits_; \
asm ("movl %k1, %k0" : "="#d(_x86bits_) : #s(data)); _x86bits_; })
#define movbb(data) movbx(data, g, g)
#define movww(data) movwx(data, g, g)
#define movll(data) movlx(data, g, g)
#define movrb(reg, data) movbx(data, reg, g)
#define movrw(reg, data) movwx(data, reg, g)
#define movrl(reg, data) movlx(data, reg, g)
#define nothing() ({ asm(" "); })
#define clobber(reg) asm("" ::: "%"#reg);
#define cmp8H(v,c) ({ bool c8hR; asm("cmpb %b2, %h1;" : \
"=@ccz"(c8hR) : "Q"(v), "Kq"(c)); c8hR; })
template<class T,class U>
typename std::common_type<T&&,U&&>::type
min(T&&a,U&&b){
if(b<a)
return std::forward<U>(b);
return std::forward<T>(a);}
template<class T,class U>
typename std::common_type<T&&,U&&>::type
max(T&&a,U&&b){
if(b>a)
return std::forward<U>(b);
return std::forward<T>(a);}
template<class T,class U,class V>
typename std::common_type<T&&,
typename std::common_type<U&&,V&&>::type>::type
min_max(T&&val,U&&low,V&&high){
if(val<low)return std::forward<U>(low);
if(val>high)return std::forward<V>(high);
return std::forward<T>(val);}
template<class T,class U>
T&min_ref(T&obj,const U&val){if(obj>val)obj=val;return obj;}
template<class T,class U>
T&min1_ref(T&obj,const U&val){if(obj>=val)obj=val-1;return obj;}
template<class T,class U>
T&max_ref(T&obj,const U&val){if(obj<val)obj=val;return obj;}
#include <algorithm>
template<typename _ForwardIterator,typename _Tp>
size_t lower_bound(_ForwardIterator __first,size_t length,const _Tp&__val)
{return std::lower_bound(__first,__first+length,__val)-__first;}
template<typename _ForwardIterator,typename _Tp,typename _Compare>
size_t lower_bound(_ForwardIterator __first,size_t length,const _Tp&__val,_Compare __comp)
{return std::lower_bound(__first,__first+length,__val,__comp)-__first;}
template<typename _ForwardIterator,typename _Tp>
size_t upper_bound(_ForwardIterator __first,size_t length,const _Tp&__val)
{return std::upper_bound(__first,__first+length,__val)-__first;}
template<typename _ForwardIterator,typename _Tp,typename _Compare>
size_t upper_bound(_ForwardIterator __first,size_t length,const _Tp&__val,_Compare __comp)
{return std::upper_bound(__first,__first+length,__val,__comp)-__first;}
TMPL2(T,U)int find(T*ptr,int count,const U&value)
{for(int i=0;i<count;i++)if(ptr[i]==value)return i;return-1;}
TMPL(T)
struct IndexRef{int offset;IndexRef(){}
IndexRef(int in){offset=in;}
operator int(){return offset;}};
struct Void{
char*data;Void()=default;
TMPL(T)Void(T in,size_t o=0){data=((char*)in)+o;}
TMPL(T)Void operator=(T in){data=(char*)in;return*this;}
TMPL(T)operator T(){return(T)data;}
TMPL(T)operator T()const{return(T)data;}
Void operator++(int){return this->data++;}
Void operator--(int){return this->data--;}
Void operator+=(Void offset){return data+=size_t(offset.data);}
Void operator-=(Void offset){return data-=size_t(offset.data);}
Void operator+(size_t offset){return data+offset;}
unsigned char&operator[](size_t n){return*(unsigned char*)(data+n);}
unsigned char&operator*(){return*(unsigned char*)(data+0);}
TMPL(T)T*&ptr(void){return*(T**)&data;}
TMPL(T)T&ref(size_t n=0){return Ref<T>(0,n);}
TMPL(T)T*ptr(size_t n){return Ptr<T>(0,n);}
BYTE&byte(size_t n=0){return Byte(0,n);}
WORD&word(size_t n=0){return Word(0,n);}
DWORD&dword(size_t n=0){return Dword(0,n);}
size_t sizet(size_t n=0){return Sizet(0,n);}
TMPL(T)T&Ref(size_t o,size_t n=0){return((T*)(data+o))[n];}
TMPL(T)T*Ptr(size_t o,size_t n=0){return&((T*)(data+o))[n];}
BYTE&Byte(size_t o,size_t n=0){return((BYTE*)(data+o))[n];}
WORD&Word(size_t o,size_t n=0){return((WORD*)(data+o))[n];}
DWORD&Dword(size_t o,size_t n=0){return((DWORD*)(data+o))[n];}
size_t&Sizet(size_t o,size_t n=0){return((size_t*)(data+o))[n];}
int offset(Void ptr){return ptr.data-data;}
void align(int size){data=(char*)((size_t(data)+(size-1))&~(size-1));}
TMPL(T)T&operator()(IndexRef<T>ref){return*(T*)(data+ref);}};
#define VOID_OPERATOR(retType) \
TMPL2(T,U) enable_if_t< \
is_cstyle_castable<T, size_t>::value \
&& is_cstyle_castable<U, size_t>::value \
&& (std::is_same<T, Void>::value \
|| std::is_same<U, Void>::value), retType>
VOID_OPERATOR(Void)operator-(const T&a,const U&b){
return(char*)(a)-(char*)(b);}
VOID_OPERATOR(bool)operator==(const T&a,const U&b){
return(char*)(a)==(char*)(b);}
VOID_OPERATOR(bool)operator!=(const T&a,const U&b){
return(char*)(a)!=(char*)(b);}
VOID_OPERATOR(bool)operator<(const T&a,const U&b){
return(char*)(a)<(char*)(b);}
VOID_OPERATOR(bool)operator>(const T&a,const U&b){
return(char*)(a)>(char*)(b);}
VOID_OPERATOR(bool)operator<=(const T&a,const U&b){
return(char*)(a)<=(char*)(b);}
VOID_OPERATOR(bool)operator>=(const T&a,const U&b){
return(char*)(a)>=(char*)(b);}
DEF_RETPAIR(VoidLen,Void,ptr,int,offset);
#ifdef __GCC_HAVE_DWARF2_CFI_ASM
asm(".macro cfia_ n; .cfi_adjust_cfa_offset \\n; .endm");
#else
asm(".macro cfia_ n; .endm");
#endif
#define free free_
#define pcpx(ph, fn) "cfia_ 4; push "#ph"; call "#fn"; cfia_ -4;"
ALWAYS_INLINE void free_(void*mem){asm(pcpx(%0,_sfree)
::"g"(mem):"memory");}
ALWAYS_INLINE void free_ref(Void&ptr){asm(pcpx(%0,_sfreer)
::"g"(&ptr):"memory");}
ALWAYS_INLINE Void malloc_(size_t sz){Void r;asm(
"call _smalloc;":"=a"(r):"a"(sz));return r;}
ALWAYS_INLINE Void realloc_(void*ptr,size_t sz){Void r;
asm(pcpx(%1,_srealloc):"=a"(r):"g"(ptr),"d"(sz));return r;}
ALWAYS_INLINE Void xmalloc(size_t sz){Void r;asm(pcpx(%1,_xmalloc)
:"=a"(r):"g"(sz));return r;}
static uint snapUpSize(uint val){return 2<<(__builtin_clz(val-1)^31);}
SHITCALL uint snapNext(uint val);
SHITCALL void freeLst(Void ptr,int count);
SHITCALL void freeLst_ref(Void&ptr,int count);
#define fclose fclose_
SHITCALL int fclose_(FILE*stream);
SHITCALL int fclose_ref(FILE*&stream);
SHITCALL Void calloc(size_t size);
TMPL(T)static inline Void realloc2(T&ptr,size_t size){Void tmp=
realloc(ptr,size);if(tmp)ptr=tmp;return tmp;}
#define malloc malloc_
#define realloc realloc_
REGCALL(2)Void xrealloc(Void&ptr,size_t size);
SHITCALL2 Void xcalloc(size_t size);SHITCALL2 Void xrecalloc(Void&ptr,size_t size);
SHITCALL2 Void xnxalloc(Void&ptr,size_t&count,size_t size);
SHITCALL2 Void nxalloc(Void&ptr,size_t&count,size_t size);
__thiscall Void xnxalloc2(void*p,size_t size);
TMPL(T)void free_ref(T*&p){free_ref(*(Void*)&p);}
TMPL(T)void freeLst_ref(T&p,int c){freeLst_ref(*(Void*)&p,c);}
#define _Realloc(n1, n2) TMPL(T) Void n1(T*& p, size_t sz) { return n1(*(Void*)&p, \
sz); } TMPL(T) Void n2(T*& p, size_t sz) { return n1(p, sz*sizeof(T)); }
_Realloc(xrealloc,xRealloc)_Realloc(xrecalloc,xRecalloc)
#define _Nxalloc(n1, n2) TMPL2(T,U) Void n1(T*& p, U& ct, size_t sz) { return n1(*(Void*)&p, \
*(size_t*)&ct, sz); } TMPL2(T,U) T& n2(T*& p, U& ct){ return *(T*)n1(p, *(size_t*)&ct, sizeof(T)); }
_Nxalloc(xnxalloc,xNextAlloc)_Nxalloc(nxalloc,NextAlloc)
#define xMalloc_(name, func) struct name { name(size_t sz) : sz(sz) {} \
operator void*() { return func(sz); } TMPL(T) \
ALWAYS_INLINE operator T*() { return (T*)func(sizeof(T)*sz); } private: size_t sz; };
xMalloc_(xMalloc,xmalloc);xMalloc_(xCalloc,xcalloc);
xMalloc_(Malloc,malloc);xMalloc_(Calloc,calloc);
SHITCALL2 Void xmemdup8(Void src,int count);
SHITCALL2 Void xmemdup16(Void src,int count);
SHITCALL2 Void xmemdup32(Void src,int count);
TMPL(T)
T*xMemdup(const T*src,int count){
if((sizeof(T)%4)==0)return xmemdup32(src,count*(sizeof(T)/4));
ei((sizeof(T)%2)==0)return xmemdup16(src,count*(sizeof(T)/2));
else return xmemdup8(src,count*sizeof(T));}
asm(".macro movsn_ n; .if \\n>=4; movsd; movsn_ \\n-4; .elseif \\n>=2; movsw;"
"movsn_ \\n-2; .elseif  \\n>=1; movsb; movsn_ \\n-1; .endif; .endm");
#define MOVSN_(d, s, n) asm volatile("movsn_ %a2" : "+D"(d), "+S"(s) : "i"(n))
#define MOVSNX_(d, s, c, n) ({int msnxc_; asm volatile("rep; movsn_ %a3" : \
"+D"(d), "+S"(s), "=c"(msnxc_) : "i"(n), "c"(c));})
#define memcpyx_ref(sz, sz2) TMPL2(T,U) \
ALWAYS_INLINE void memcpy##sz##_ref(T*& dst, U*& src, size_t count) { \
if(__builtin_constant_p(count) && (((count*sz2/4)+((count*sz2)&3)) <= 6)) { \
MOVSN_(dst, src, sz2*count); } else { MOVSNX_(dst,src,count,sz2);}} \
TMPL(T) ALWAYS_INLINE T* memcpy##sz(T* dst, const void* src, size_t count) \
{ memcpy##sz##_ref(dst, src, count); return dst; }
memcpyx_ref(8,1);memcpyx_ref(16,2);memcpyx_ref(32,4);
#define _memcpy_sz(macro) { \
if((sizeof(T) % 4) == 0) macro(32, count*(sizeof(T)/4)) \
ei((sizeof(T) % 2) == 0) macro(16, count*(sizeof(T)/2)) \
else macro(8, count*sizeof(T)) }
#define _rep_memcpy_sz_(size, count) \
memcpy##size##_ref(dst, src, count);
TMPL2(T,U)ALWAYS_INLINE
void memcpy_ref(T*&dst,U*&src,size_t count){
_memcpy_sz(_rep_memcpy_sz_);}
TMPL(T)ALWAYS_INLINE Void memcpyX(T*dst,const void*src,
size_t count){memcpy_ref(dst,src,count);return dst;}
TMPL(T)ALWAYS_INLINE Void memcpyY(T*dst,const void*src,
size_t count){memcpy_ref(dst,src,count);return src;}
#define memsetx_ref(sz, inst, init...) template<class T,class U> \
ALWAYS_INLINE void memset##sz##_ref(T*&dst,size_t count,const U&src){ init; \
if(__builtin_constant_p(count) && (count <= 6)) while(count--) \
asm volatile(#inst :"=D"(dst) :"a"(src),"D"(dst)); \
else asm volatile("rep "#inst :"=D"(dst),"=c"(count) \
:"a"(src),"D"(dst),"c"(count)); } template<class T,class U> \
ALWAYS_INLINE T*memset##sz(T*dst,size_t count,const U&src){ \
memset##sz##_ref(dst,count,src);return dst; }
memsetx_ref(8,stosb,byte val=src);
memsetx_ref(16,stosw,typename std::conditional<sizeof(U)<2
,word,const U&>::type val=src;)
memsetx_ref(32,stosl,typedef typename std::conditional<std::
is_same<double,U>::value,float,const U&>::type type;
typename std::conditional<sizeof(U)<4,uint,type>::type val=src)
template<class T,class U>
void memset_ref(T*&dst,size_t count,const U&src){
if(sizeof(T)==4)memset32_ref(dst,count,src);
ei(sizeof(T)==2)memset16_ref(dst,count,src);
else memset8_ref(dst,count,src);}
template<class T,class U>T*memsetX(T*dst,size_t count,const U&src){
memset_ref(dst,count,src);return dst;}
template<class T,class U,size_t N>
void memsetX(T(*array)[N],size_t count,const U&val){
memsetX((T*)array,N*count,val);}
template<class T,class U,size_t N>
void memsetX(T(&array)[N],const U&val){
memsetX(array,N,val);}
template<class T,class U,size_t N,size_t M>
void memsetX(T(&array)[N][M],const U&val){
memsetX(array,N,val);}
#define _rep_memset_sz_(size, count) \
memset##size##_ref(dst, count, fill);
template<class T>
void memfill_ref(T*&dst,size_t count,size_t fill){
_memcpy_sz(_rep_memset_sz_);}
template<class T>
T*memfillX(T*dst,size_t count,size_t fill=0){
memfill_ref(dst,count,fill);return dst;}
template<class T>void memfillX(T&obj,size_t fill=0){
memfillX(&obj,1,fill);}
#define memfill2(dst_, dstEnd, fill) { \
uint byteLen = RangeOf(dst_, dstEnd); char* dst = (char*)&dst_; \
if(!__builtin_constant_p(byteLen)) memset8_ref(dst,byteLen,(char)fill); \
ei((byteLen % 4) == 0) memset32_ref(dst,byteLen/4,fill); \
ei((byteLen % 2) == 0) memset16_ref(dst,byteLen/2,(word)fill); \
else { memset8(dst,byteLen,(char)fill); } \
__assume(dst == ((char*)&dst_)+byteLen); }
REGCALL(2)void*memswap(
void*p1,void*p2,size_t sz);
template<class Type,class Next>constexpr
bool is_one_of(const Type&needle,const Next&next)
{return needle==next;}
template<class Type,class Next,class ... Rest>constexpr
bool is_one_of(const Type&needle,const Next&next,const Rest&... haystack)
{return needle==next||is_one_of(needle,haystack...);}
template<class T,class U,class V>constexpr bool inRng(
T t,U u,V v){return(t>=u)&&(t<=v);}
template<class T,class U,class V>constexpr bool inRng1(
T t,U u,V v){return(t>=u)&&(t<v);}
constexpr u8 rol_8(u8 val,int shift){return(val<<shift)|(val>>(8-shift));}
constexpr u8 ror_8(u8 val,int shift){return(val>>shift)|(val<<(8-shift));}
constexpr u16 rol_16(u16 val,int shift){return(val<<shift)|(val>>(16-shift));}
constexpr u16 ror_16(u16 val,int shift){return(val>>shift)|(val<<(16-shift));}
constexpr u32 rol_32(u32 val,int shift){return(val<<shift)|(val>>(32-shift));}
constexpr u32 ror_32(u32 val,int shift){return(val>>shift)|(val<<(32-shift));}
#define isPathSep(...) is_one_of(__VA_ARGS__, '\\', '/')
#define isPathSep2(...) is_one_of(__VA_ARGS__, '\\', '/', ':')
#define isDigit(x) inRng(x, '0', '9')
#define _CEXPCHOP_(T) \
REGCALL(1) constexpr static T toUpper(T ch){ return((ch>='a') &&(ch<='z'))?ch-32:ch;} \
REGCALL(1) constexpr static T toLower(T ch){ return((ch>='A') &&(ch<='Z'))?ch+32:ch;}
_CEXPCHOP_(char)_CEXPCHOP_(int)
REGCALL(1)constexpr static bool isAlpha(int ch){
return unsigned((ch&~0x20)-'A')<26;}
template<class T,class U,class V>
bool ptrAddChk(T p1,U len,V*&p2){size_t tmp;
bool ret=__builtin_add_overflow((size_t)p1,len,&tmp);
p2=(V*)tmp;return ret;}
template<class T,class U,class V>
ALWAYS_INLINE bool ovfchk(T a,U b,V c){typeof(a)tmp;
if(__builtin_constant_p(c)&&(c==1))return b>=a;
if(__builtin_add_overflow(b,c,&tmp))return true;
nothing();return(tmp>a);}
template<class T,class U,class V>
ALWAYS_INLINE bool ovfchkU(T a,U b,V c){
return ovfchk(uns(a),uns(b),uns(c));}
template<class T,class U,class V,class W=int>
bool ovfAddBos(T&out,U b,V o,W s=1){typeof(out)S;
return(__builtin_mul_overflow(o,s,&S))
||__builtin_add_overflow(b,S,&out);}
template<class T,class U,class V,class W=int>
bool ovfAddBosU(T&out,U b,V o,W s=1){return
ovfAddBos(unsR(out),uns(b),uns(o),uns(s));}
template<class T,class U,class V=int>
T*ovfAddPosU(T*p,U o,V s=1){
if(ovfAddBosU(RT(&p),RT(&p),o,s))
return 0;return notNull(p);}
#ifdef __SSE4_1__
#define _DFC_(n, t, x, m) static inline t MCAT(f,n)(t f) { \
asm("ROUNDP" #x " $" #m ", %1, %0" : "=x"(f) : "x"(f)); return f; } \
static inline int MCAT(i,n)(t f) { f = MCAT(f,n)(f); int y; asm( \
"cvtts"#x"2si %1, %0" : "=g"(y) : "x"(f)); return y; }
#else
#define _DFC_(n, t, x, m) static inline t MCAT(f,n)(t f) { asm("call _f" \
#n : "+t"(f)); return f; } static inline int MCAT(i,n)(t f) { int y; \
asm("call _i"#n : "=a"(y) : "t"(f) : "st"); return y; }
#endif
_DFC_(floor,float,S,1);_DFC_(floor,double,D,1);
_DFC_(ceil,float,S,2);_DFC_(ceil,double,D,2);
#undef _DFC_
extern const uint powersOf10[10];
extern const byte tableOfHex[2][16];
static inline void lrintf(int&dst,float x){
__asm__ __volatile__
("fistpl %0":"=m"(dst):"t"(x):"st");}
#define IS_PTR(x) (size_t(x) >= 65536)
void*__thiscall xRngPtr_get(void**ptr,size_t size);
TMPL(T)struct xRngPtr{
T*data;T*end_;
xRngPtr()=default;
xRngPtr(const xRngPtr&that)=default;
xRngPtr(T*d,int l):data(d),end_(d+l){}
xRngPtr(T*d,T*e):data(d),end_(e){}
T*begin(){return data;}
T*end(){return end_;}
operator T*(){return data;}
int count(){return end_-data;}
int offset(T*pos){return pos-data;}
T*operator->(){return data;}
xRngPtr&operator++(){data++;return*this;}
ALWAYS_INLINE bool chk(){return end_>data;}
ALWAYS_INLINE bool chk(int size){return count()>=size;}
ALWAYS_INLINE T&f(){return*data;}
ALWAYS_INLINE T&l(){return end_[-1];}
ALWAYS_INLINE T&fi(){return*data++;}
ALWAYS_INLINE T&ld(){return*--end_;};
ALWAYS_INLINE bool chk(T*cp){return end_>cp;}
ALWAYS_INLINE bool chk2(){ARGFIX(end_);return chk();}
ALWAYS_INLINE bool chk2(T*cp){ARGFIX(end_);return chk(cp);}
Void get(size_t len){return Void(
xRngPtr_get((void**)this,len));}};
#define XARRAY_COMMON(C, T, len) \
C() = default; C(const C& that) = default; \
C(const T* d, int l) : data((T*)d), len(l) {} \
C(const T* d, const T* e) : data((T*)d), len(e-d) {} \
template<typename... Args> C& init(Args... args) \
{ return *this = C(args...); } void clear() { free(); init(); } \
void init(){ data=0; len=0; } void free() { ::free(data); } \
C release() { return {::release(data), ::release(len) }; } \
C get() { return {data, len}; } \
void setbase( T* pos) { len += data-pos; data = pos; } \
void setend(T* pos) { len = pos-data; } int offset( \
T* pos) { return pos - data; } DEF_BEGINEND(T, data, len); \
C left(int i) { return C(data, i); } \
C right(int i) { return C(data+i, len-i); } \
C endRel(int i) { return C(end(), i-len); } \
ALWAYS_INLINE xRngPtr<T> ptr() { return xRngPtr<T>{data, end()}; } \
ALWAYS_INLINE void set(xRngPtr<T> ptr) { init(ptr.data, ptr.end_); } \
ALWAYS_INLINE void sete(xRngPtr<T> ptr) { setend(ptr.end_); }
TMPL(T)struct xarray{
T*data;union{size_t len;size_t size;};
XARRAY_COMMON(xarray,T,len);
template<int l>xarray(T(&d)[l]):xarray((T*)d,l){}
size_t ofsGet(T&ref){return PTRDIFF(&ref,data);}
T&ofsRef(size_t ofs){return*(T*)Void(data,ofs);}
void Free(){for(auto&ref:*this)ref.~T();this->free();}
void Clear(){this->Free();this->init();}
T*xAlloc(size_t size){T*ptr=xalloc(size);
for(int i=0;i<size;i++)pNew(ptr+i);}
template<typename... Args>T&push_back(Args...
args){return rNew(xnxalloc(),args...);}
void pop_back(void){len--;end()->~T();}
T&back(void){return end()[-1];}
T*xalloc(size_t size){return data=xMalloc(len=size);}
T*xcalloc(size_t size){return data=xCalloc(len=size);}
T*xresize(size_t size){return xRealloc(data,len=size);}
T&xnxalloc(){return*(T*)xnxalloc2(this,sizeof(T));}
T&ib(){return data[len++];}
T*xcopy(const xarray&that){return xcopy(that.data,that.len);}
T*xcopy(const T*di,size_t ci){len=ci;return(data=xMemdup(di,ci));}
T*xCopy(const xarray&that){return xCopy(that.data,that.len);}
T*xCopy(const T*di,size_t ci){if(!hasDtorp(di))return xcopy(di,ci);
T*ptr=xalloc(ci);for(int i=0;i<ci;i++)pNew(ptr+i,di[i]);return ptr;}
TMPL(U=T)bool chk(size_t idx,size_t ln=1){
static_assert(!(sizeof(U)%sizeof(T)));return
(!__builtin_mul_overflow(ln,sizeof(U)/sizeof(T),
&ln)&&(!ovfchkU(size,idx,ln)));}
TMPL(U=T)U*getp(size_t idx,size_t ln=1){
return chk<U>(idx,ln)?notNull((U*)(data+idx)):0;}
TMPL(U=T)U&getr(size_t idx){return*(U*)(data+idx);}
TMPL2(U=T,V=U)bool chk2u(u32&t,u32 b,u32 l=1)
{static_assert(!(sizeof(U)%sizeof(T)));return
!ovfAddBosU(t,b,l,sizeof(U)/sizeof(T))&&(t<=len);}
TMPL2(U=T,V=U)std::pair<U*,V*>getp2u(u32 b,u32 l=1)
{u32 t;if(!chk2u<U,V>(t,b,l))return{0,0};return
{notNull((U*)(data+b)),(V*)(data+t)};}};
TMPL(T)struct xArray:xarray<T>{
xArray():xarray<T>(0,0){}
~xArray(){this->Free();}
xArray(const xarray<T>&that):xarray<T>(that){}
xArray(const xArray&that){this->xCopy(that);}};
struct xvector_{
Void dataPtr;size_t dataSize,allocSize;
void init_(){ZINIT;}
void init_(Void buff,int buffSize){
dataPtr=buff;dataSize=0;allocSize=buffSize;}
void free_(){free_ref(dataPtr);}
void clear_(){free_();dataSize=0;allocSize=0;}
Void release_(void){return::release(dataPtr);}
Void xalloc_(size_t size);
Void xreserve_(size_t size);Void xresize_(size_t size);
VoidLen xnxalloc2_(size_t size);VoidLen xrxalloc2_(size_t size);
Void xnxalloc_(size_t size){return xnxalloc2_(size);}
Void xrxalloc_(size_t size){return xrxalloc2_(size);}
Void begin(size_t offset=0){return dataPtr+offset;}
Void end(size_t offset=0){return dataPtr+dataSize+offset;}
size_t addSize(size_t val){return::release(dataSize,dataSize+val);}
size_t setEnd(Void endPos){return::release(dataSize,endPos-dataPtr);}
TMPL(T)
T&operator()(IndexRef<T>ref){return dataPtr(ref);}
#define _xvector_write_(sz, count) return write##sz(src,count);
TMPL(T)int write(const T*src,int count){
_memcpy_sz(_xvector_write_);}
TMPL(T)int write(const T&val){
if(sizeof(T)==1)return write8(CAST(byte,val));
ei(sizeof(T)==2)return write16(CAST(word,val));
ei(sizeof(T)==4)return write32(CAST(uint,val));
ei(sizeof(T)==8)return write64(CAST(INT64,val));
else write(&val,1);}
RetEdx<int>write8(Void src,int count);
RetEdx<int>write16(Void src,int count);
RetEdx<int>write32(Void src,int count);
RetEdx<int>write8(byte);RetEdx<int>write16(word);
RetEdx<int>write32(uint);RetEdx<int>write64(INT64);
RetEdx<int>strcat2(const char*str);
RetEdx<int>strcat2(const WCHAR*str);
int strcat(const char*str);
int strcat(const WCHAR*str);
void fmtcat(const char*fmt,...);
void fmtcat(const WCHAR*fmt,...);
Void xcopy_(Void di,size_t sz);
void remove_(Void di,size_t sz);};
TMPL(T)
struct xvector:xvector_{
xvector(){}
xvector(const xvector<T>&That){init(That);}
xvector(T*di,size_t ci){init(di,ci);}
xvector(T*di,size_t ds,size_t as){init2(di,ds,as);}
int offset(T*ptr){return ptr-(T*)dataPtr;}
size_t getCount()const{return dataSize/sizeof(T);}
size_t getAlloc()const{return allocSize/sizeof(T);}
DEF_BEGINEND(T,dataPtr,dataSize);
xvector<T>release2(void){xvector<T>result=*this;
this->init();return result;}
void Free(){if(std::is_trivially_destructible<T>::value)
{this->free_();}else{dtor();}}
void Clear(){this->Free();dataSize=0;allocSize=0;}
T*xAlloc(size_t size){T*ptr=xalloc(size);
for(int i=0;i<size;i++)pNew(ptr);}
T*xReserve(size_t size){return xreserve_(size*sizeof(T));}
T*xNalloc(size_t size){T*ptr=xnalloc(size);
for(int i=0;i<size;i++)pNew(ptr+i);}
template<typename... Args>
T&push_back(Args... args){return rNew(*xnalloc(1),args...);}
void pop_back(void){addCount(-1);end()->~T();}
T&back(void){return end()[-1];}
T*xRalloc(size_t size){return xrxalloc_(size*sizeof(T));}
void addCount(size_t val){dataSize+=(val*sizeof(T));}
void setCount(size_t val){dataSize=(val*sizeof(T));}
void init(const xvector<T>&That){init2(That.dataPtr,That.dataSize,That.allocSize);}
void init(T*di,size_t ci){init2(di,ci*sizeof(T),ci*sizeof(T));}
void init2(T*di,size_t ds,size_t as){
this->dataPtr=di;this->dataSize=ds;this->allocSize=as;}
xvector<T>get2()const{return*this;}
T*xalloc(size_t size){return this->xalloc_(size*sizeof(T));}
T*xresize(size_t size){return xresize_(size*sizeof(T));}
T*xnalloc(size_t size){return xnxalloc_(size*sizeof(T));}
T*xCopy_(Void di,size_t sz){if(std::is_trivially_destructible<T>::value)
{return xcopy_(di,sz);}else{return ctor(di,sz);}}
T*xCopy(const T*di,size_t ci){return xCopy_(di,ci*sizeof(T));}
T*xCopy(const xarray<T>&That){return xCopy(That.data,That.len);}
T*xCopy(const xvector<T>&That){return xCopy_(That.dataPtr,That.dataSize);}
T*xcopy(const T*di,size_t ci){return xcopy_(di,ci*sizeof(T));}
T*xcopy(const xarray<T>&That){return xcopy(That.dataPtr,That.count);}
T*xcopy(const xvector<T>&That){return xcopy_(That.dataPtr,That.dataSize);}
void remove(T*elem){remove_(elem,sizeof(T));}
private:
__attribute__((noinline))T*ctor(T*di,size_t sz){
T*dstPos=xalloc_(sz);T*endPos=Void(di,sz);
while(dstPos<endPos){pNew(dstPos,*di);
dstPos++;di++;}return dataPtr;}
__attribute__((noinline))void dtor(){if(dataPtr){
for(auto&obj:*this)obj.~T();::free(dataPtr);}}};
TMPL(T)
struct xVector:xvector<T>{
xVector(){xvector_::init_();}
xVector(const xarray<T>&That){this->xCopy(That);}
xVector(const T*di,size_t ci){this->xCopy(di,ci);}
xVector(const xArray<T>&That){this->xCopy(That);}
xVector(const xvector<T>&That){this->xCopy(That);}
xVector(const xVector<T>&That){this->xCopy(That);}
xVector(xVector<T>&&That){this->init2(
That.dataPtr,That.dataSize,That.allocSize);}
~xVector(){this->Free();}};
TMPL(T)struct cstr_;typedef cstr_
<char>cstr;typedef cstr_<WCHAR>cstrW;
TMPL(T)struct Cstr_;typedef Cstr_
<char>Cstr;typedef Cstr_<WCHAR>CstrW;
TMPL(T)struct xstr_;typedef xstr_
<char>xstr;typedef xstr_<WCHAR>wxstr;
#define CSTRFN1_(nm) REGCALL(2) NCSTR nm(NCSTR str); SHITCALL NCSTR nm(NCCH* str);
#define CSTRFN2_(nm) SHITCALL NCSTR nm(NCSTR n1, NCSTR n2); SHITCALL \
NCSTR nm(NCSTR n1, NCCH* n2); SHITCALL NCSTR nm(NCCH* n1, NCCH* n2);
#define CSTRTH1_(nm) SHITCALL NCSTR nm(NCCH* str) { return nm(NCSTR(str)); }
#define CSTRTH2_(nm) SHITCALL NCSTR nm(NCSTR n1, NCCH* n2) { return \
nm(n1, NCSTR(n2)); } SHITCALL NCSTR nm(NCCH* n1, NCCH* n2) { \
return nm(NCSTR(n1), n2); }
typedef const char cch;
typedef const WCHAR cchw;
TMPL(T)SHITCALL cstr_<T>cstr_alc(int len);
#define cmpi(m1,m2) (toUpper(m1)==toUpper(m2))
#define CMPI(m1, m2, lab) if(!cmpi(m1,m2)) goto NS;
#define CMPS(m1, m2, lab) if(m1-m2) goto NS;
#define CMPL(len, cmp) int i = 0; do { cmp; } while(++i < len);
#define CSTRG(n) NCHR* MCAT(str,n), int MCAT(len,n)
#define CSTRS(n) NCSTR(MCAT(str,n), MCAT(len,n))
#define CSTRX(s) s, (s).slen
#define CSTRFN4_(nm) cstr SHITCALL nm(CSTRG(1), char ch);
TMPL(T)struct cstr_{
T*data;int slen;
XARRAY_COMMON(cstr_,T,slen);
ALWAYS_INLINE cstr_(const T*d);
template<int l>cstr_(const T(&d)[l]):cstr_(d,l-1){}
DEF_RETPAIR(prn_t,int,slen,T*,data);
prn_t prn(){return prn_t(slen,data);}
cstr_ nterm(void){if(data)
*end()='\0';return*this;}
bool chk(uint idx){return(idx<slen);}
T get(uint idx){return chk(idx)?data[idx]:0;}
T getr(uint idx){return get(idx+slen);}
bool sepReq(){return!isPathSep2(getr(-1),'\0');}
int cmp(cstr_ s){return cstr_cmp(CSTRX(*this),CSTRX(s));}
int icmp(cstr_ s){return cstr_icmp(CSTRX(*this),CSTRX(s));}
int cmp(const T*s){return cstr_cmp(CSTRX(*this),s);}
int icmp(const T*s){return cstr_icmp(CSTRX(*this),s);}
cstr_ str(cstr_ s){return cstr_str(CSTRX(*this),CSTRX(s));}
cstr_ istr(cstr_ s){return cstr_str(CSTRX(*this),CSTRX(s));}
cstr_ str(const T*s){return cstr_str(CSTRX(*this),s);}
cstr_ istr(const T*s){return cstr_istr(CSTRX(*this),s);}
cstr_ chr(T ch){return cstr_chr(CSTRX(*this),ch);}
cstr_ rchr(T ch){return cstr_rchr(CSTRX(*this),ch);}
cstr_ chr2(T ch){return cstr_chr2(CSTRX(*this),ch);}
cstr_ rchr2(T ch){return cstr_rchr2(CSTRX(*this),ch);}
cstr_ xdup(void)const{return cstr_dup(*this);}
void free(const T*p){if(p!=data)free();}};
void test1(cch*x,int len);
#define OPEQU(t,a,b) t& operator=(a){b; return *this; }
#define CTOREQU(t,a,m,r,v) t(a):m(v){} OPEQU(t,a,r(v))
TMPL(T)struct Cstr_:cstr_<T>{
void reset(cstr_<T>str={}){this->free();init(str);}
Cstr_():cstr_<T>(0,0){}
ALWAYS_INLINE~Cstr_(){this->free();}
CTOREQU(Cstr_,const cstr_<T>&t,cstr_<T>,reset,t);
CTOREQU(Cstr_,const Cstr_&t,cstr_<T>,reset,t.xdup());
CTOREQU(Cstr_,Cstr_&&t,cstr_<T>,reset,t.release());};
struct bstr:cstr{
int mlen;
bstr()=default;
bstr(cch*);bstr(cstr that);
bstr&operator=(const cstr&that){
return strcpy(that);}
struct ZT{};bstr(ZT zt):
cstr(0,0),mlen(0){}
bstr&strcpy(const char*);bstr&strcpy(cstr);
bstr&strcat(const char*);bstr&strcat(cstr);
bstr&fmtcpy(const char*,...);
bstr&fmtcat(const char*,...);
bstr&pathcat(cch*);bstr&pathcat(cstr);
bstr&pathend(cch*);bstr&pathend(cstr);
bstr&argcat(cch*);bstr&argcat(cstr);
bstr&argcatf(cch*);bstr&argcatf(cstr);
REGCALL(1)cstr nullTerm(void);
SHITCALL cstr calcLen(void);
SHITCALL cstr updateLen(void);
REGCALL(2)char*xreserve(int len);
REGCALL(2)char*xresize(int len);
REGCALL(2)char*xralloc(int len);
REGCALL(2)char*xnalloc(int len);
void push_back(char c);
DEF_RETPAIR(alloc_t,bstr*,
This,int,len_);
REGCALL(2)alloc_t alloc(int len);};
struct Bstr:bstr{
using bstr::bstr;
Bstr():bstr(ZT()){}
~Bstr(){::free(this->data);}};
TMPL(T)struct xstr_{
typedef cstr_<T>U;
T*data;operator T*(){return data;}void init(T*p){
data=p;}void reset(T*p=0){free(data);init(p);}
T*release(T*p=0){T*t=data;data=p;return t;}
cstr xdup()const{return xstrdup(*(U*)this);}
bool operator==(const T*s)const{return!strcmp(data,s);}
constexpr xstr_():data(0){}
ALWAYS_INLINE~xstr_(){free(data);}
xstr_(T*p):data(p){}xstr_&operator=
(T*p){reset(p);return*this;}
xstr_(const xstr_&u)=delete;xstr_&operator=
(const xstr_&u){reset(u.xdup());return*this;}
xstr_(xstr_&&u):data(u.release()){}xstr_&operator=(
xstr_&&u){reset(u.release());return*this;}
xstr_(U p):data(p){}xstr_&operator=(
U p){reset(p);return*this;}
void alloc(int len){data=xMalloc(len+1);}};
#define NWIF(x,y) MIF(NWIDE,x,y)
#define NCCH NWIF(cchw, cch)
#define NCHR NWIF(WCHAR, char)
#define NCSTR NWIF(cstrW, cstr)
#define NWTX NWIF("W", "")
#define NWNM(x) NWIF(MCAT(x,W),x)
TMPL(T)
struct xstrfmt_fmtN{enum{FLAG_ABSLEN=1<<16,
SPACE_POSI=1,FLAG_XCLMTN=2,FLAG_QUOTE=4,FLAG_HASH=8,
FLAG_DOLAR=16,FLAG_PRCNT=32,FLAG_AMPRSND=64,FLAG_APOSTR=128,
FLAG_LBRACE=256,FLAG_RBRACE=512,UPPER_CASE=1024,FORCE_SIGN=2048,
FLAG_COMMA=4096,LEFT_JUSTIFY=8192,FLAG_SLASH=1<<15,PADD_ZEROS=1<<16};
va_list ap;T*dstPosArg;uint flags;
int width;int precision;int length;
typedef size_t(*cbfn_t)(xstrfmt_fmtN*ctx,
T ch);void*cbCtx;cbfn_t cbfn;};
#define xstrfmt_fmt xstrfmt_fmtN<char>
#define xstrfmt_fmtW xstrfmt_fmtN<wchar_t>
#define Xstrfmt(...) xstr_(xstrfmt(__VA_ARGS__))
#define NWIDE 0
ALWAYS_INLINE bool isNull(NCCH*str){
return!str||!str[0];}
ALWAYS_INLINE NCSTR cstr_len(NCCH*si){NCSTR so;asm("push %1; call "
"_cstr_len" MIF(NWIDE,"W",""):"=A"(so):"g"(si));return so;}
REGCALL(2)NCSTR cstr_dup(NCSTR str);
int SHITCALL cstr_cmp(CSTRG(1),CSTRG(2));
int SHITCALL cstr_icmp(CSTRG(1),CSTRG(2));
int SHITCALL cstr_cmp(CSTRG(1),NCCH*str2);
int SHITCALL cstr_icmp(CSTRG(1),NCCH*str2);
NCSTR SHITCALL cstr_str(CSTRG(1),CSTRG(2));
NCSTR SHITCALL cstr_istr(CSTRG(1),CSTRG(2));
NCSTR SHITCALL cstr_str(CSTRG(1),NCCH*str2);
NCSTR SHITCALL cstr_istr(CSTRG(1),NCCH*str2);
SHITCALL NCSTR cstr_split(cstr&str,NCHR ch);
CSTRFN4_(cstr_chr)CSTRFN4_(cstr_rchr)
CSTRFN4_(cstr_chr2)CSTRFN4_(cstr_rchr2)
SHITCALL NCSTR xstrdup(NCCH*);
SHITCALL NCSTR xstrdup(NCCH*,size_t);
SHITCALL NCHR*xstrdupr(NCHR*&,NCCH*);
SHITCALL NCHR*xstrdupr(NCHR*&,NCCH*,size_t);
SHITCALL NCHR*strScmp(NCCH*,NCCH*);
SHITCALL NCHR*strSicmp(NCCH*,NCCH*);
SHITCALL int strEcmp(NCCH*,NCCH*);
SHITCALL int strEicmp(NCCH*,NCCH*);
SHITCALL int strNcpy(NCHR*,NCCH*,int);
SHITCALL int removeCrap(NCHR*);
SHITCALL int strmove(NCHR*,NCCH*);
SHITCALL NCHR*strstr(NCCH*,NCCH*,int maxLen);
SHITCALL NCHR*strstri(NCCH*,NCCH*,int maxLen);
SHITCALL int strcmp2(NCCH*str1,NCCH*str2);
SHITCALL int stricmp2(NCCH*str1,NCCH*str2);
SHITCALL NCSTR strcpyn(NCHR*,NCCH*,int);
SHITCALL bool strcmpn(NCCH*,NCCH*,int);
SHITCALL bool stricmpn(NCCH*,NCCH*,int);
CSTRFN1_(getPath)CSTRFN1_(getName)
CSTRFN1_(getName2)CSTRFN1_(getExt)
CSTRFN2_(replName)CSTRFN2_(pathCat)
CSTRFN2_(replNameF)CSTRFN2_(pathCatF)
CSTRFN2_(fullNameRepl)CSTRFN2_(fullNameCat)
static inline NCSTR getPath0(NCSTR str){
return getPath(str).nterm();}
CSTRFN1_(getName3)CSTRFN2_(replExt)
static inline bool isRelPath(NCCH*str){bool ret;asm(
"call _isRelPath0"NWTX:"=c"(ret):"a"(str));return ret;}
static inline bool isRelPath(NCSTR str){bool ret;asm(
"call _isRelPath"NWTX:"=c"(ret):"A"(str));return ret;}
SHITCALL NCSTR xstrfmt(void*cbCtx,xstrfmt_fmtN<NCHR>::
cbfn_t cbfn,VaArgFwd<NCCH*>va);
SHITCALL NCSTR xstrfmt(void*cbCtx,xstrfmt_fmtN<NCHR>::
cbfn_t cbfn,NCCH*,...);
SHITCALL NCSTR xstrfmt(VaArgFwd<NCCH*>va);
SHITCALL NCSTR xstrfmt(NCCH*,...);
SHITCALL int strfmt(NCHR*buffer,NCCH*fmt,...);
SHITCALL int xstrfmt_len(VaArgFwd<NCCH*>va);
SHITCALL NCHR*xstrfmt_fill(NCHR*buffer,
VaArgFwd<NCCH*>va);
#undef NWIDE
#define NWIDE 1
ALWAYS_INLINE bool isNull(NCCH*str){
return!str||!str[0];}
ALWAYS_INLINE NCSTR cstr_len(NCCH*si){NCSTR so;asm("push %1; call "
"_cstr_len" MIF(NWIDE,"W",""):"=A"(so):"g"(si));return so;}
REGCALL(2)NCSTR cstr_dup(NCSTR str);
int SHITCALL cstr_cmp(CSTRG(1),CSTRG(2));
int SHITCALL cstr_icmp(CSTRG(1),CSTRG(2));
int SHITCALL cstr_cmp(CSTRG(1),NCCH*str2);
int SHITCALL cstr_icmp(CSTRG(1),NCCH*str2);
NCSTR SHITCALL cstr_str(CSTRG(1),CSTRG(2));
NCSTR SHITCALL cstr_istr(CSTRG(1),CSTRG(2));
NCSTR SHITCALL cstr_str(CSTRG(1),NCCH*str2);
NCSTR SHITCALL cstr_istr(CSTRG(1),NCCH*str2);
SHITCALL NCSTR cstr_split(cstr&str,NCHR ch);
CSTRFN4_(cstr_chr)CSTRFN4_(cstr_rchr)
CSTRFN4_(cstr_chr2)CSTRFN4_(cstr_rchr2)
SHITCALL NCSTR xstrdup(NCCH*);
SHITCALL NCSTR xstrdup(NCCH*,size_t);
SHITCALL NCHR*xstrdupr(NCHR*&,NCCH*);
SHITCALL NCHR*xstrdupr(NCHR*&,NCCH*,size_t);
SHITCALL NCHR*strScmp(NCCH*,NCCH*);
SHITCALL NCHR*strSicmp(NCCH*,NCCH*);
SHITCALL int strEcmp(NCCH*,NCCH*);
SHITCALL int strEicmp(NCCH*,NCCH*);
SHITCALL int strNcpy(NCHR*,NCCH*,int);
SHITCALL int removeCrap(NCHR*);
SHITCALL int strmove(NCHR*,NCCH*);
SHITCALL NCHR*strstr(NCCH*,NCCH*,int maxLen);
SHITCALL NCHR*strstri(NCCH*,NCCH*,int maxLen);
SHITCALL int strcmp2(NCCH*str1,NCCH*str2);
SHITCALL int stricmp2(NCCH*str1,NCCH*str2);
SHITCALL NCSTR strcpyn(NCHR*,NCCH*,int);
SHITCALL bool strcmpn(NCCH*,NCCH*,int);
SHITCALL bool stricmpn(NCCH*,NCCH*,int);
CSTRFN1_(getPath)CSTRFN1_(getName)
CSTRFN1_(getName2)CSTRFN1_(getExt)
CSTRFN2_(replName)CSTRFN2_(pathCat)
CSTRFN2_(replNameF)CSTRFN2_(pathCatF)
CSTRFN2_(fullNameRepl)CSTRFN2_(fullNameCat)
static inline NCSTR getPath0(NCSTR str){
return getPath(str).nterm();}
CSTRFN1_(getName3)CSTRFN2_(replExt)
static inline bool isRelPath(NCCH*str){bool ret;asm(
"call _isRelPath0"NWTX:"=c"(ret):"a"(str));return ret;}
static inline bool isRelPath(NCSTR str){bool ret;asm(
"call _isRelPath"NWTX:"=c"(ret):"A"(str));return ret;}
SHITCALL NCSTR xstrfmt(void*cbCtx,xstrfmt_fmtN<NCHR>::
cbfn_t cbfn,VaArgFwd<NCCH*>va);
SHITCALL NCSTR xstrfmt(void*cbCtx,xstrfmt_fmtN<NCHR>::
cbfn_t cbfn,NCCH*,...);
SHITCALL NCSTR xstrfmt(VaArgFwd<NCCH*>va);
SHITCALL NCSTR xstrfmt(NCCH*,...);
SHITCALL int strfmt(NCHR*buffer,NCCH*fmt,...);
SHITCALL int xstrfmt_len(VaArgFwd<NCCH*>va);
SHITCALL NCHR*xstrfmt_fill(NCHR*buffer,
VaArgFwd<NCCH*>va);
#undef NWIDE
TMPL(T)cstr_<T>::cstr_(const T*d):cstr_(cstr_len(d)){}
#define UTF816L(rt, ty) DEF_RETPAIR(rt, int, \
size, const ty*, endp); UTF816A(rt, utf816_size, ty)
#define UTF816A(rt,fn,ty) rt __stdcall fn(const ty* mbstr_); \
rt __stdcall fn(const ty* mbstr_, int len);
UTF816L(utf816_size_tW,char);UTF816L(utf816_size_t8,wchar_t);
UTF816A(cstrW,utf816_dup,char);UTF816A(cstr,utf816_dup,wchar_t);
#define UTF816B(t1, t2) t1* __stdcall utf816_cpy(t1* wstr_, t2* mbstr_); \
t1* __stdcall utf816_cpy(t1* wstr_, t2* mbstr_, int len);
UTF816B(char,const wchar_t);
#define UTF816CP_(nm,dn,sn) WCHAR* __stdcall MCAT(utf816_cpy,nm)( \
WCHAR* dst, MIF(dn, (int dstMax,),) cch* src MIF(sn, (,int len),))
UTF816CP_(,0,0);UTF816CP_(,0,1);UTF816CP_(,1,0);UTF816CP_(,1,1);
UTF816CP_(_,0,0);UTF816CP_(_,0,1);UTF816CP_(_,1,0);UTF816CP_(_,1,1);
int __stdcall utf816_size2(cch*,int);
WCHAR*__stdcall utf816_cpy2_(WCHAR*,cch*,int);
WCHAR*__stdcall utf816_cpy2(WCHAR*,cch*,int);
cstrW __stdcall utf816_dup2(cch*,int);
cstrW __stdcall utf816_strLst_dup(cch*str);
#define UNICODE_MAX 0x10FFFF
#define UTF8_GET2(ch,s,e) ({ void* t; asm("call _UTF8_GET2" \
: "+a"(ch), "+S"(s), "=d"(t) : "d"(e)); });
#define UTF816_LEN8B(ch,s,e,l) if(s8(ch)<0) { \
UTF8_GET2(ch,s,e); if(ch>>16) ADDP(l,1); }
#define UTF816_CPY8B(ch,d,s,e) ({ void* t; asm("call _UTF8_GET2; " \
"call _UTF16_PUT1" : "+a"(ch), "+S"(s), "+D"(d), "=d"(t) : "d"(e)); })
#define UTF16_GET1(ch,s) ({ asm("call _UTF8_GET1" \
: "+a"(ch), "+S"(s) :: "edx"); });
#define UTF8_GET2(ch,s,e) ({ void* t; asm("call _UTF8_GET2" \
: "+a"(ch), "+S"(s), "=d"(t) : "d"(e)); });
int __stdcall utf8_cmpi(cch*s1,cch*s2);
int __stdcall utf8_cmpi(cch*s1,int l1,WCHAR*s2);
#include <shlobj.h>
#define isIHV(x) ((x) == INVALID_HANDLE_VALUE)
static inline void setTxtMode(FILE*fp,bool ena){
_setmode(fp->_file,ena?0x4000:0x8000);}
HMODULE _stdcall getModuleBase(void*ptr);
enum{
ESC_LEAQUOT=1,ESC_CPMODE=2,ESC_SFEQUOT=4,
ESC_ENVEXP=32,ESC_ENTQUOT=128};
cstrW REGCALL(3)getFullPath_(cstrW str_,int mode);
#define getNtPathNameX(s) xstr_(getNtPathName(s).data)
BOOL WINAPI setWindowText(HWND,cch*);
BOOL WINAPI setDlgItemText(HWND,int,cch*);
int WINAPI messageBox(HWND,cch*,cch*,UINT);
BOOL WINAPI createProcess(LPCSTR,LPCSTR,LPSECURITY_ATTRIBUTES,
LPSECURITY_ATTRIBUTES,BOOL,DWORD,LPVOID,LPCSTR,
LPSTARTUPINFOA,LPPROCESS_INFORMATION);
BOOL WINAPI setCurrentDirectory(cch*);
cstr narrowFree(LPWSTR s);
ALWAYS_INLINE wxstr widen(cch*s){
return utf816_dup(s);}
cstrW ansi_to_wide_dup(cch*ansi,int len);
#define W32SARD_(l,g) WCHAR* ws; int sz = l+1; \
ws = xMalloc (sz); return {ws, g};
#define W32SARD2_(l,g) WCHAR* ws=0; int sz = l; if(sz) \
{ ws = xMalloc(sz+=1); sz = g; } return {ws,sz};
struct WIN32_FIND_DATAU{
DWORD dwFileAttributes;FILETIME ftCreationTime;
FILETIME ftLastAccessTime;FILETIME ftLastWriteTime;
u64p4 nFileSize;DWORD reparseAttrib;
DWORD fnLength;char cFileName[MAX_PATH*3];
void init(WIN32_FIND_DATAW*src);
cstr cStr(){return{cFileName,fnLength};}
bool isDir(){return dwFileAttributes&0x10;}};
#define NWIDE 0
int __stdcall cmd_escape_len(NCCH*src,size_t len,int flags);
NCHR*REGCALL(1)cmd_escape(NCHR*dst,NCCH*src,size_t len,int flags);
int sysfmt(NCCH*fmt,...);
NCSTR WINAPI getFullPath(NCCH*str);NCSTR REGCALL(2)getFullPath(NCSTR str);
NCSTR WINAPI getFullPathF(NCCH*str);NCSTR REGCALL(2)getFullPathF(NCSTR str);
cstrW WINAPI getNtPathName(NCCH*s);cstrW REGCALL(2)getNtPathName(NCSTR s);
HANDLE WINAPI createFile(NCCH*,DWORD,DWORD,
LPSECURITY_ATTRIBUTES,DWORD,DWORD,HANDLE);
DWORD WINAPI getFileAttributes(NCCH*);
BOOL WINAPI createDirectory(NCCH*,LPSECURITY_ATTRIBUTES);
BOOL WINAPI copyFile(NCCH*,NCCH*,BOOL);
BOOL WINAPI moveFile(NCCH*,NCCH*);
BOOL WINAPI moveFileEx(NCCH*,NCCH*,DWORD);
BOOL WINAPI deleteFile(NCCH*);
BOOL WINAPI setFileAttributes(NCCH*,DWORD);
NCSTR WINAPI NWNM(getWindowText)(HWND);
NCSTR WINAPI NWNM(getWindowText2)(HWND);
NCSTR WINAPI NWNM(getDlgItemText)(HWND,int);
NCSTR WINAPI NWNM(getDlgItemText2)(HWND,int);
NCSTR WINAPI NWNM(getModuleFileNameEx)(HANDLE,HMODULE);
NCSTR WINAPI NWNM(getModuleFileName)(HMODULE);
NCSTR WINAPI NWNM(getProgramDir)(void);
NCSTR WINAPI NWNM(shGetFolderPath)(int nFolder);
NCSTR WINAPI getEnvironmentVariable(NCCH*name);
NCSTR WINAPI expandEnvironmentStrings(NCCH*env);
int REGCALL(1)findFirstFile(HANDLE&,NCCH*,
NWIF(WIN32_FIND_DATAW,WIN32_FIND_DATAU)*);
int WINAPI findNextFile(HANDLE,
NWIF(WIN32_FIND_DATAW,WIN32_FIND_DATAU)*);
bool WINAPI isFullPath(NCCH*path);
#undef NWIDE
#define NWIDE 1
int __stdcall cmd_escape_len(NCCH*src,size_t len,int flags);
NCHR*REGCALL(1)cmd_escape(NCHR*dst,NCCH*src,size_t len,int flags);
int sysfmt(NCCH*fmt,...);
NCSTR WINAPI getFullPath(NCCH*str);NCSTR REGCALL(2)getFullPath(NCSTR str);
NCSTR WINAPI getFullPathF(NCCH*str);NCSTR REGCALL(2)getFullPathF(NCSTR str);
cstrW WINAPI getNtPathName(NCCH*s);cstrW REGCALL(2)getNtPathName(NCSTR s);
HANDLE WINAPI createFile(NCCH*,DWORD,DWORD,
LPSECURITY_ATTRIBUTES,DWORD,DWORD,HANDLE);
DWORD WINAPI getFileAttributes(NCCH*);
BOOL WINAPI createDirectory(NCCH*,LPSECURITY_ATTRIBUTES);
BOOL WINAPI copyFile(NCCH*,NCCH*,BOOL);
BOOL WINAPI moveFile(NCCH*,NCCH*);
BOOL WINAPI moveFileEx(NCCH*,NCCH*,DWORD);
BOOL WINAPI deleteFile(NCCH*);
BOOL WINAPI setFileAttributes(NCCH*,DWORD);
NCSTR WINAPI NWNM(getWindowText)(HWND);
NCSTR WINAPI NWNM(getWindowText2)(HWND);
NCSTR WINAPI NWNM(getDlgItemText)(HWND,int);
NCSTR WINAPI NWNM(getDlgItemText2)(HWND,int);
NCSTR WINAPI NWNM(getModuleFileNameEx)(HANDLE,HMODULE);
NCSTR WINAPI NWNM(getModuleFileName)(HMODULE);
NCSTR WINAPI NWNM(getProgramDir)(void);
NCSTR WINAPI NWNM(shGetFolderPath)(int nFolder);
NCSTR WINAPI getEnvironmentVariable(NCCH*name);
NCSTR WINAPI expandEnvironmentStrings(NCCH*env);
int REGCALL(1)findFirstFile(HANDLE&,NCCH*,
NWIF(WIN32_FIND_DATAW,WIN32_FIND_DATAU)*);
int WINAPI findNextFile(HANDLE,
NWIF(WIN32_FIND_DATAW,WIN32_FIND_DATAU)*);
bool WINAPI isFullPath(NCCH*path);
#undef NWIDE
struct xvectorW__{
byte*data;union{struct{
u16 size,msize;};u32 size_;};
void nalloc_(u32 ns,u32 sz);
void nalloc2_(u32 ns,u32 sz){
if(ns>msize)nalloc_(ns,sz);}
void init(void){data=0;size_=0;}
void clear(void);void free(){::free(data);}
NEVER_INLINE byte*xreserve(u32 ns,u32 sz);
NEVER_INLINE byte*xresize(u32 ns,u32 sz);
NEVER_INLINE byte*xnalloc2(u32 ns,u32 sz);
NEVER_INLINE byte*xncalloc2(u32 ns,u32 sz);
NEVER_INLINE byte*xnalloc(u32 sz);
NEVER_INLINE byte*xnalloc(u32 ds,u32 sz);
NEVER_INLINE byte*xnralloc(u32 ds,u32 sz);
NEVER_INLINE byte*xncalloc(u32 ds,u32 sz);};
template<int sz>
struct xvectorW_:xvectorW__{
byte*xreserve(u32 ns){return xvectorW__::xreserve(ns,sz);}
byte*xresize(u32 ns){return xvectorW__::xresize(ns,sz);}
byte*xnalloc2(u32 ns){return xvectorW__::xnalloc2(ns,sz);}
byte*xncalloc2(u32 ns){return xvectorW__::xncalloc2(ns,sz);}
byte*xnalloc(void){return xvectorW__::xnalloc(sz);}
byte*xnalloc(u32 ds){return xvectorW__::xnalloc(ds,sz);}
byte*xnralloc(u32 ds){return xvectorW__::xnralloc(ds,sz);}
byte*xncalloc(u32 ds){return xvectorW__::xncalloc(ds,sz);}};
TMPL(T)struct xvectorW{
T*data;u16 size,msize;
DEF_BEGINEND(T,data,size);
void init(void){BT().init();}
void clear(void){BT().clear();}
void free(){BT().free();}
void Clear(){Free();data=0;BT().size_=0;}
void Free(){if(hasDtorT(T))dtor();else free();}
template<typename... Args>T&push_back(Args...
args){return*pNew(xnalloc(),args...);}
void pop_back(void){size--;end()->~T();}
T&back(void){return end()[-1];}
T&ib(){return data[size++];}
T*xreserve(u32 ns){return(T*)BT().xreserve(ns);}
T*xresize(u32 ns){return(T*)BT().xresize(ns);}
T*xnalloc2(u32 ns){return(T*)BT().xnalloc2(ns);}
T*xncalloc2(u32 ns){return(T*)BT().xncalloc2(ns);}
T*xnalloc(void){return(T*)BT().xnalloc();}
T*xnalloc(u32 ds){return(T*)BT().xnalloc(ds);}
T*xnralloc(u32 ds){return(T*)BT().xnralloc(ds);}
T*xncalloc(u32 ds){return(T*)BT().xncalloc(ds);}
private:
xvectorW_<sizeof(T)>&BT(void){return*(xvectorW_<sizeof(T)>*)this;}
__attribute__((noinline))void dtor(){if(data){
for(auto&obj:*this)obj.~T();::free(data);}}};
TMPL(T)struct xVectorW:xvectorW<T>{
xVectorW(){this->init();}
~xVectorW(){this->Free();}};
SHITCALL Void memmem(const void*b1,
const void*b2,size_t len1,size_t len2);
template<class F>
class finally_type{F function;
public:finally_type(F f):function(f){}
__attribute__((always_inline))~finally_type(){function();}};
template<class F>finally_type<F>
finally(F f){return finally_type<F>(f);}
#define SCOPE_EXIT(f) auto MCAT(sExit, __COUNTER__) = \
finally([&](void) __attribute__((always_inline)) {f;})
#define SCOPE_REF(T,R,M) T R=M; SCOPE_EXIT(M=R)
template<typename T>struct Range1_type2
{T value;
Range1_type2(T in):value(in){}
T operator*(){return value;}
bool operator!=(const Range1_type2<T>&that)const
{return that.value!=value;}
void operator++(){value++;}};
template<typename T>class Range1_type{
public:Range1_type(T start,T end):
begin_(start),end_(end){}
Range1_type2<T>begin(){return begin_;}
Range1_type2<T>end(){return end_;}
Range1_type2<T>begin_,end_;};
template<typename T>class Range2_type{
public:Range2_type(T*collection,size_t size):
mCollection(collection),mSize(size){}
T*begin(){return&mCollection[0];}
T*end(){return&mCollection[mSize];}
private:T*mCollection;size_t mSize;};
template<typename T>
Range1_type<T>Range(T start,T end)
{return Range1_type<T>(start,end);}
template<typename T>
Range2_type<T>Range(T*array,size_t size)
{return Range2_type<T>(array,size);}
#define bswap32 __builtin_bswap32
#define bswap16 __builtin_bswap16
static inline
char*stradd(char*dst,const char*src){
char ch;while(lodsb(src,ch),ch)stosb(dst,ch);
*dst=ch;return dst;}
static inline
wchar_t*stradd(wchar_t*dst,cchw*src){
wchar_t ch;while(lodsw(src,ch),ch)stosw(dst,ch);
*dst=ch;return dst;}
SHITCALL void xfread(void*,size_t,size_t,FILE*);
SHITCALL void xfwrite(const void*,size_t,size_t,FILE*);
SHITCALL void xchsize(FILE*fp,long size);
SHITCALL int fsize(FILE*fp);
SHITCALL xarray<byte>loadFile(FILE*fp,int extra=0);
SHITCALL xarray<char>loadText(FILE*fp);
SHITCALL char**loadText(FILE*fp,int&LineCount);
SHITCALL int saveFile(cch*fName,void*data,size_t size);
int xvfprintf(FILE*stream,const char*format,va_list arg);
int xfprintf(FILE*stream,const char*format,...);
void xfputs(const char*str,FILE*stream);
SHITCALL void xfclose(FILE*fp);
SHITCALL void xfclose_ref(FILE*&fp);
TMPL(T)void xfread(T*ptr,size_t size,FILE*fp){xfread(ptr,sizeof(T),size,fp);}
TMPL(T)void xfwrite(const T*ptr,size_t size,FILE*fp){xfwrite(ptr,sizeof(T),size,fp);}
TMPL(T)void xfread(T&ptr,FILE*fp){xfread(&ptr,1,fp);}
TMPL(T)void xfwrite(const T&ptr,FILE*fp){xfwrite(&ptr,1,fp);}
template<typename T,int size>void xfread(T(&ptr)[size],FILE*fp){xfread(ptr,size,fp);}
template<typename T,int size>void xfwrite(T(&ptr)[size],FILE*fp){xfwrite(ptr,size,fp);}
inline FILE*fopen(cchw*fName,cchw*mode)
{return _wfopen(fName,mode);}
inline wchar_t*fgets(wchar_t*str,int num,FILE*fp)
{return fgetws(str,num,fp);}
inline size_t strlen(cchw*str){return wcslen(str);}
inline size_t strnlen(cchw*s,size_t l){return wcsnlen(s,l);}
inline wchar_t*strcpy(wchar_t*d,cchw*s){return wcscpy(d,s);}
inline int strcmp(cchw*str1,cchw*str2){return wcscmp(str1,str2);}
inline int stricmp(cchw*str1,cchw*str2){return wcsicmp(str1,str2);}
inline int strncmp(cchw*str1,cchw*str2,size_t num){return wcsncmp(str1,str2,num);}
inline int strnicmp(cchw*str1,cchw*str2,size_t num){return wcsnicmp(str1,str2,num);}
inline wchar_t*strdup(cchw*str){return wcsdup(str);}
inline int vsprintf(wchar_t*s,cchw*format,va_list arg){
return vswprintf(s,format,arg);}
inline int system(cchw*s){return _wsystem(s);}
template<typename T,int size>
int strncmp(const T*str1,const T(&str2)[size])
{return strncmp(str1,str2,size-1);}
template<typename T,int size>
int strnicmp(const T*str1,const T(&str2)[size])
{return strnicmp(str1,str2,size-1);}
TMPL2(T,F)void qsort(T*base,size_t num,F compar)
{typedef int(*qcomp)(const T&,const T&);
qsort(base,num,sizeof(*base),(Void)(qcomp)compar);}
TMPL2(T,F)void qsort(T&array,F compar)
{qsort(std::begin(array),std::end(array)-std::begin(array),compar);}
TMPL2(T,F)T*bsearch(void*key,T*base,size_t num,F compar)
{typedef int(*qcomp)(const T&,const T&);return(T*)
bsearch(key,base,num,sizeof(*base),(Void)(qcomp)compar);}
TMPL2(T,F)T*bsearch(void*key,T&array,F compar){return
bsearch(key,std::begin(array),std::end(array)-std::begin(array),compar);}
extern const char progName[];
void contError(HWND hwnd,const char*fmt,...);
FATALFUNC void fatalError(const char*fmt,...);
FATALFUNC void fatalError(HWND hwnd,const char*fmt,...);
FATALFUNC void errorAlloc();
FATALFUNC void errorMaxPath();
FATALFUNC void errorDiskSpace();
FATALFUNC void errorDiskWrite();
FATALFUNC void errorDiskFail();
FATALFUNC void errorBadFile();
TMPL(T)T errorAlloc(T ptr)
{if(!ptr)errorAlloc();return ptr;}
SHITCALL int fopen_ErrChk(void);
SHITCALL FILE*xfopen(const char*,const char*);
SHITCALL char*xfgets(char*,int,FILE*);
SHITCALL xarray<byte>loadFile(const char*fileName,int extra=0);
SHITCALL xarray<char>loadText(cch*fName);
SHITCALL char**loadText(const char*fileName,int&LineCount);
extern const char mem_zp4[];
#endif
