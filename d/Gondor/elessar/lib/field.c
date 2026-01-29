/*
 *     This file is obsolete and has been replaced by:
 *		/d/Gondor/common/lib/field.c
 *
 *	Please do not use this file in new code and
 *	replace it where it is used in old files!
 *
 *		Olorin, June 1995
 */
/*     The standard Field-of-Gondor-file, made by Elessar for Genesis   */
/*     February 1992. No copyrights, but would like to have my name     */
/*     mentioned if anyone modifies this file for own use.  :-)         */
/*
 *
 * Modification log:
 * - added reset_room() to reset seached to 0, so new herbs will grow.
 *   files which inherit this file should include ::reset_room() if
 *   reset_room() is redefined.
 *   Olorin, October 1993
 * - added a standard fail message for 'climb ....' *   when areatype is 
 *   'Trees' (3) or 'Forest' (7), or the rooms has the item 'tree' added.
 *   Olorin, November 1993
 *
 */

inherit "/d/Gondor/common/lib/field";
