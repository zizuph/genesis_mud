#ifndef _TOR_ABBEY_SHOPBASE
#define _TOR_ABBEY_SHOPBASE
// index constants for item_list. List in the form of:
// ({ ({"pattern1","path1",cost1,level1}), ({"ptrn2","path2",c2,l2}), etc })
#define  IL_PC_NDX              0
#define  IL_FNAME_NDX           1
#define  IL_PRICE_NDX           2
#define  IL_MIN_BUY_LEVEL_NDX   3
 
// constants for replies of shopkeeper
#define SKR_BUY_NOT_SPEC        0
#define SKR_DONT_HAVE           1
#define SKR_NOT_ALLOWED_TO_SELL 2
#define SKR_SELL_FAIL           3
#define SKR_TELL_PRICE          4
#endif
