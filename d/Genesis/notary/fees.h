/*
 * 2003-09-17 by Dargoth
 * Notarial service fees.
 * As the service is intended to be mud-wide, the fees
 * should generally be fixed and similar at all places.
 * 
 */
#ifndef __NOTARY_FEES_
#define __NOTARY_FEES_

#ifdef DEBUG_MODE
#define PLATINUMS 0
#else
/* the fee has been lowered to see if it'd help bring more business */
#define PLATINUMS 12
// #define PLATINUMS 1728
#endif
    
#define PROCESSING_FEE (5*PLATINUMS) /* 5pc */
#define COPY_FEE (5*PLATINUMS) /* 5pc */
#define VIEW_FEE 0

/* how long the documents are preserved initially,
   without having to pay the fee */    
#define INITIAL_EXPIRY 600

#define HOUR 3600
#define DAY (HOUR*24)
#define WEEK (DAY*7)
#define MONTH (DAY*30)
   
/*
   Possible storage times.
 */ 
mapping storage_times=
    ([  "1 week": WEEK,
        "1 month": MONTH,
        "3 months": (MONTH*3),
        "6 months": (MONTH*6),
        "1 year": (MONTH*12)
    ]);

/* storage fees for private, guild and public access
   respectively, in pc, FEE_* macros should correspond 
   to storage_fees mapped array size
 */
#define FEE_PRIVATE 0
#define FEE_GUILD 1
#define FEE_PUBLIC 2

mapping storage_fees=
    ([
        WEEK:({ 5, 10, 30 }),
        MONTH:({ 10, 20, 60 }),
        (MONTH*3):({ 20, 40, 120 }),
        (MONTH*6):({ 30, 60, 180 }),
        (MONTH*12):({ 50, 100, 300 })
     ]);

#endif
