/* Redefinition of do_die for _all_ npcs inside the Keep to make */
/* the Knight guards aggressive towards the killer.              */
void
do_die(object killer)
{
    if (!killer->query_prop("_i_attacked_in_vingaard"))
	killer->add_prop("_i_attacked_in_vingaard", 1);
    if (!killer->query_prop(I_WAS_EVIL))
	killer->add_prop(I_WAS_EVIL, 1);
    ::do_die(killer);
}
