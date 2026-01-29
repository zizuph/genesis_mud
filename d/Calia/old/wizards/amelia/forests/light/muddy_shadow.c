/*
*  borrowed by Amelia
*/

inherit "/std/shadow";

varargs public mixed
query_adj(int arg)
{
	return ({"muddy", "wet"});
}

int
query_wet_shadow()
{
	return 666;
}

destruct_wet_shadow()
{
	call_out("remove_shadow", 1000);
}
