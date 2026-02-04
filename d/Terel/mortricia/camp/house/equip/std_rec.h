/*
 * This is an include that can be used for standard objects that, by default,
 * should be recoverable. Notice that it only works for objects that aren't
 * modified after they have been cloned. It that case you must store the
 * modified parts (special properties etc.) through an own-written
 * query_recover() and init_recover(string arg). See
 *     ~mortricia/load/t_ring.c 
 * for an example of this.
 */

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
