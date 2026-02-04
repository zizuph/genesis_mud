
void
break_armour(object ob)
{
    object *all;
    int i;

    all = all_inventory(ob);

    for (i=0; i<sizeof(all); i++) {
	if (!function_exists("create_armour", all[i])) continue;
	if (all[i]->query_worn() == ob) {
	    ob->catch_msg("The forceful kick hit your " +
			      all[i]->short() + ".\n");
	    all[i]->remove_broken();
	    return;
	}
    }
    ob->catch_msg("The forceful kick hit you " +
		  "right in the solar plexus!\n");
    i = 320 + random(400) - ob->query_stat(SS_CON);
    if (i<100) i = 100;
    ob->reduce_hit_point(i);
    if (ob->query_hp() <= 0) ob->do_die(TO);
}
