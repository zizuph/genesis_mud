/*
 * Function name: find_wep
 * Description  : Finds if a spear is wielded
 * Arguments    : object who - wielder
 *                int polearm - find any weapon, or a polearm
 * Returns      : object weapon - the spear
 */
object
find_wep(object who, int polearm = 1)
{
    object *weapons = who->query_weapon(-1);
 
    switch(sizeof(weapons))
    {
    case 1:
        if (polearm)
        {
            if (weapons[0]->weapon_type() == "polearm")
                return weapons[0];
        }
        else
        {
            return weapons[0];
        }
        return 0;

    case 2:
        if (polearm)
        {
            if (weapons[0]->weapon_type() == "polearm" &&
              weapons[1]->weapon_type() == "polearm")
            {
                if (weapons[0]->query_hit() + weapons[0]->query_pen() >
                  weapons[1]->query_hit() + weapons[1]->query_pen())
                    return weapons[0];
                else
                    return weapons[1];
            }
            else if (weapons[0]->weapon_type() == "polearm")
                return(weapons[0]);
            else if (weapons[1]->weapon_type() == "polearm")
                return weapons[1];
        }
        else
        {
            if (weapons[0]->query_hit() + weapons[0]->query_pen() >
              weapons[1]->query_hit() + weapons[1]->query_pen())
                return weapons[0];
            else
                return weapons[1];
        }
        return 0;

    default:
        return 0;
    }
}
