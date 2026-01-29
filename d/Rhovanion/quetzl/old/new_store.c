#include <macros.h>
 
static int maxlist;
 
public void
set_maxlist(int x)
{
    maxlist = x;
}
 
public string
change_ob(object ob)
{
    string ret;
    ret = ob->query_recover();
    if (!strlen(ret))
        ret = MASTER_OB(ob);
    return ret;
}
 
public void
remove_object()
{
    int i, j;
    object *oblist;
    string *oblist_str = ({ });
    oblist = all_inventory(this_object());
    i = sizeof(oblist);
    j = i/10;
    while(j--)
        oblist_str += ({ change_ob(oblist[random(i)]) });
    setuid();
    seteuid(getuid());
    save_map(([ "objects" : oblist_str ]), MASTER);
    return;
}
 
public void
recover_item(string arg)
{
    string d1, d2;
    object ob;
    setuid();
    seteuid(getuid());
    if (sscanf(arg, "%s:%s", d1, d2) != 2)
    {
        clone_object(arg)->move(this_object());
        return;
    }
    ob = clone_object(d1);
    d1->init_recover(d2);
    d1->move(this_object());
}
 
public void
recover_items()
{
    string *obs;
    int i;
    setuid();
    seteuid(getuid());
    obs = restore_map(MASTER)["objects"];
    i = sizeof(obs);
    while(i--)
        recover_item(obs[i]);
}
 
public void
do_enter_inv(object ob, object from)
{
    int i, j;
    i = sizeof(all_inventory(this_object()));
    if (i > maxlist)
        j = maxlist - 3;
    else
         return;
    slice_array(all_inventory(this_object()), j, i - 1)->remove_object();
}
