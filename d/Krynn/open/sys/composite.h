/*

  composite.h

  Description routines, composite sentences

  Contains only the additions: THE_COMPOSITE_DEAD, THE_COMPOSITE_LIVE,
                               NOART_COMPOSITE_DEAD, NOART_COMPOSITE_LIVE.
*/
#ifndef COMPOSITE_DEF_KRYNN
#define COMPOSITE_DEF_KRYNN

#define COMPOSITE_FILE_KRYNN "/d/Krynn/open/sys/global/composite"

/* Same as COMPOSITE_LIVE and COMPOSITE_DEAD, except that you can give your own
 * article which is then put in front of _each_ item. Example:
 * 'his red shirt, his blue pants and his green boots.'
 */
#define MYART_COMPOSITE_LIVE(x,y) ((string)COMPOSITE_FILE_KRYNN->myart_desc_live(x,0,y))
#define MYART_COMPOSITE_DEAD(x,y) ((string)COMPOSITE_FILE_KRYNN->myart_desc_dead(x,0,y))

/*
 * A VBFC to FO_COMPOSITE_LIVE and _DEAD would be nice :)
 */
#define QCOMPLIVE_KRYNN "@@fo_desc_live:" + COMPOSITE_FILE_KRYNN + "@@"
#define QCOMPDEAD_KRYNN "@@fo_desc_dead:" + COMPOSITE_FILE_KRYNN + "@@"

#endif

