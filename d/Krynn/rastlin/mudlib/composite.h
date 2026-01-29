/*

  composite.h

  Description routines, composite sentences
*/
#ifndef COMPOSITE_DEF
#define COMPOSITE_DEF

#define COMPOSITE_FILE "/d/Krynn/rastlin/mudlib/composite"


/*
 * Standard composite descriptions for living and dead objects
 *
 * Usable in 2.4.6 and in 3.0
 *
 */
#define COMPOSITE_LIVE(x) ((string)COMPOSITE_FILE->desc_live(x))
#define COMPOSITE_DEAD(x) ((string)COMPOSITE_FILE->desc_dead(x))

#define FO_COMPOSITE_LIVE(x, ob) ((string)COMPOSITE_FILE->fo_desc_live(x, ob))
#define FO_COMPOSITE_DEAD(x, ob) ((string)COMPOSITE_FILE->fo_desc_dead(x, ob))

/*
 * Function:    composite
 * Description: Creates a composite description of objects
 * Arguments:   x:          Array of the objects to describe
 *              sf:         Function to call in objects to get its <name>
 *                          Objects with the same <names> are described
 *                          together.
 *              df:         Function to call to get the actual description of
 *                          a group of 'same objects' i.e objects whose
 *                          'sf' returned the same value.
 *              ob:         Object to call df in.
 *
 *		for_ob:     Who want this description?
 * 
 * Returns:     A description string on the format:
 *              <desc>, <desc> and <desc> 
 *              Where <desc> is what ob->df() returns
 *
*/
#define COMPOSITE(x, sf, df, ob) \
    ((string)COMPOSITE_FILE->composite(x, sf, df, ob))

#define FO_COMPOSITE(x, sf, df, ob, for_ob) \
    ((string)COMPOSITE_FILE->fo_composite(x, sf, df, ob, for_ob))

/*
 * Returns the array of unique objects from the last call to COMPOSITE
 *
 * Usable only in 3.0
 */
#define COMPOSITE_OBLAST ((object *)COMPOSITE_FILE->get_last_objects())

/*
 * Function:    composite_sort
 * Description: Sorts an array as composite sorts its output
 * Arguments:   arr:        Array of the objects to sort
 *              sepfnc:     Function to call in objects to get its <name>
 *                          Objects with the same <names> are sorted
 *                          together.
 * 
 * Returns:     0 or the array sorted
 *
*/
#define COMPOSITE_SORT(arr, sepfnc) \
    ((object *)COMPOSITE_FILE->sort_similar(arr, sepfnc))

/*
 * A VBFC to FO_COMPOSITE_LIVE and _DEAD would be nice :)
 */
#define QCOMPLIVE "@@fo_desc_live:" + COMPOSITE_FILE + "@@"
#define QCOMPDEAD "@@fo_desc_dead:" + COMPOSITE_FILE + "@@"

/*
 * COMPOSITE_WORDS
 *
 * Simple combination of a wordlist with "," and "and"
 */
#define COMPOSITE_WORDS(wl)	((string)COMPOSITE_FILE->composite_words(wl))

#endif
