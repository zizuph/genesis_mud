inherit "/std/board";

#define TP this_player()

int
can_access()
{
    if (TP->query_dragonarmy_occ_member())
	return 1;
    return 0;
}

int
allow_rank(int i)
{
    if (TP->query_dragonarmy_promotions() >= i)
	return 1;
    return 0;
}

int
allow_color(string c)
{
    if (TP->query_dragonarmy_division() == c)
	return 1;
    return 0;
}

int
allow_wiz(int krynn_only = 0)
{
    string dom;
    dom = lower_case("/secure/master"->query_wiz_dom(TP->query_real_name()));


    if (TP->query_wiz_level() && (!krynn_only || dom == "ansalon" || dom == "krynn"))
	return 1;
    return 0;
}
