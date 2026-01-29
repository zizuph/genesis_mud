/* DONT USE THIS CODE
 * 
 * This is ancient and does not correctly persist items. 
 * 
 * Cotillion - 2020-04-13
 */

/*
 * This is an include that can be used for standard objects that, by default,
 * should be recoverable. Notice that it only works for objects that aren't
 * modified after they have been cloned. It that case you must store the
 * modified parts (special properties etc.) through an own-written
 * query_recover() and init_recover(string arg). See
 *     ~mortricia/camp/q_ring.c
 * for an example of this.
 */


#ifdef THIS_IS_BROKEN

string
query_recover()
{
    return explode(file_name(this_object()) + "#", "#")[0] + ":";
}


void
init_recover(string arg)
{
    return;
}
#endif

