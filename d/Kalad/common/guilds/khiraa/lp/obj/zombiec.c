inherit "/std/object";
#include "../../khiraa.h"
#include "../../default.h"

object *zombies = ({});

void dispell();
void add_zombie(object ob);
int query_zombies();


int
do_list()
{
    int i,cur;
    string res = "";
    if(query_zombies() == 0)
    {
        remove_object();
        return 0;
    }
    for(i = 0; i < sizeof(zombies); i++)
    {
        cur = i + 1;
        if(objectp(zombies[i]))
        {
            res += "zombie";
            res += cur;
            res += " - ";
            res +=
            find_object("/cmd/live/state")->show_subloc_health(zombies[i],TP)+
            "\n";
        }
    }
    if(!strlen(res))
        write("There are no zombies listed.\n");
    else
        write(res);
    return 1;
}


int
do_move(string str)
{
    int z_num;
    NF("You must provide syntax as: zmove zombie(#)\n");
    if(!str)
        return 0;
    if(sscanf(str,"zombie%d",z_num) != 1)
        return 0;
    NF("There is no valid zombie number '"+z_num+"'.\n");
    if(z_num > sizeof(zombies) || !objectp(zombies[z_num - 1]))
        return 0;
    zombies[z_num -1]->zombie_move();
    write("You have commanded zombie"+z_num+" to randomly move.\n");
    return 1;
}

int
do_smove(string str)
{
    int z_num;
    NF("You must provide syntax as: zsmove zombie(#)\n");
    if(!str)
        return 0;
    if(sscanf(str,"zombie%d",z_num) != 1)
        return 0;
    NF("There is no valid zombie number '"+z_num+"'.\n");
    if(z_num > sizeof(zombies) || !objectp(zombies[z_num - 1]))
        return 0;
    zombies[z_num -1]->zombie_smove();
    write("You have commanded zombie"+z_num+" to stop moving.\n");
    return 1;
}

int
do_destroy(string str)
{
    write("You destroy all zombies you control.\n");
    dispell();
    return 1;
}

void
init()
{
    ::init();
    add_action(do_move,"zmove");
    add_action(do_smove,"zsmove");
    add_action(do_list,"zlist");
    add_action(do_destroy,"zdestroy");
}


void
create_object()
{
    set_name("_zombiec_");
    add_prop(OBJ_I_WEIGHT,0);
    add_prop(OBJ_I_VOLUME,0);
    add_prop(OBJ_M_NO_DROP,1);
    set_no_show();
}

void
add_zombie(object monst)
{
    int i;
    for(i = 0; i < sizeof(zombies); i++)
    {
        if(!objectp(zombies[i]))
            zombies[i] = monst;
    }
    zombies += ({ monst });
}

int
query_zombies()
{
    int i,sum;
    for(i = 0; i < sizeof(zombies); i++)
    {
        if(objectp(zombies[i]))
            sum++;
    }
    return sum;
}

void
dispell()
{
    int i;
    for(i = 0; i < sizeof(zombies); i++)
    {
        tell_room(E(zombies[i]),"The "+zombies[i]->short()+" suddenly "+
        "fades away!\n");
        zombies[i]->remove_object();
    }
    remove_object();
}
