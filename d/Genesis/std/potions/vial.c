inherit "/obj/potion_vial";

/* Make it so that people start recovering the new stanard vial. */
string
query_recover()
{
    return "/obj/potion_vial:" + num_heap();
}
