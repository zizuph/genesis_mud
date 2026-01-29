// Random leggings for Avenir ogres
// made by Boriska

#include <macros.h>
#include <stdproperties.h>
#include <wa_types.h>

inherit "/std/armour";

static string *adjs = ({ "smelly", "dusty", "dirty", "blooded" });
static int adj_len = sizeof(adjs);

// make sure the quality improves for bigger indices
static string *materials = ({"copper", "bronze", "iron" });
static int mat_len = sizeof(materials);

static string *longs = ({
  "Heavy and bulky piece of armour with traces of long and\n" +
  "careless usage about it.\n"
});

static int adj, mat, lon, long_len = sizeof(longs);


public void configure_me(void);


public void
create_armour(void)
{
    set_name("leggings");
    set_short("leggings");

    adj = random(adj_len);
    mat = random(mat_len);
    lon = random(long_len);

    configure_me();
}

public void
configure_me(void)
{
    set_short( adjs[adj] + " " + materials[mat] + " " + "leggings");
    add_adj(adjs[adj]);
    set_ac(7 + mat * 3);
    set_long(longs[lon]);
    set_at(A_LEGS);
    add_prop(OBJ_I_WEIGHT, 3000 + 500 * mat );
    add_prop(OBJ_I_VOLUME, 3000 ); 
}

public string
query_recover(void)
{
    return MASTER + ":" + query_arm_recover() +
	sprintf ("hjhj#%d#%d#%d#", adj, mat, lon);
}

public void
init_recover(string arg)
{
    string foo;

    remove_adj(adjs[adj]);

    sscanf( arg, "%shjhj#%d#%d#%d#%s", foo, adj, mat, lon, foo);
    init_arm_recover(arg);
    configure_me();
}
