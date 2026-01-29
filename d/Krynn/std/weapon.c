/*
 * This is the Krynn Standard Weapon
 *
 * - set_npc_hit
 * - set_npc_pen
 *     These functions allow special hit and pen values to be set 
 *     when the weapon is wielded by a npc.
 */
inherit "/std/weapon";

static int npc_hit, npc_pen;

/*
 * Function Name: set_npc_hit
 * Description  : Sets the hit value the weapon should have when wielded
 *                by a npc.
 */
void
set_npc_hit(int i)
{
    npc_hit = i;
}

/*
 * Function Name: set_npc_pen
 * Description  : Sets the pen value the weapon should have when wielded
 *                by a npc.
 */
void
set_npc_pen(int i)
{
    npc_pen = i;
}

/*
 * Function name: query_npc_hit
 * Description:   Query the to npc hit value in the weapon
 */
int
query_npc_hit()
{
    return npc_hit;
}

/*
 * Function name: query_npc_pen
 * Description:   Query the npc pen value in the weapon
 */
int
query_npc_pen()
{
    return npc_pen;
}

/*
 * Function Name: query_pen
 * Description  : This is a mask of query_pen to make 
 *                the pen value dependant on the wielder.
 *                Npcs use another pen value of one has been set.
 */
int
query_pen()
{
    if (npc_pen && wielder->query_npc())
        return npc_pen;

    return ::query_pen();
}

/*
 * Function Name: query_hit
 * Description  : This is a mask of query_hit to make 
 *                the hit value dependant on the wielder.
 *                Npcs use another pen value of one has been set.
 */
int
query_hit()
{
    if (npc_hit && wielder->query_npc())
        return npc_hit;
    
    return ::query_hit();
}

/*
 * Function Name: stat_object
 * Description  : Some extra information for the curious
 *                wizard.
 */
string
stat_object()
{
    string ret;

    ret = ::stat_object();

    if (npc_hit)
        ret += "Special NPC hit value: " + npc_hit + "\n";
    if (npc_hit)
        ret += "Special NPC pen value: " + npc_pen + "\n";
    return ret;
}
