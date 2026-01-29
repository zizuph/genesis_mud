/*
 * /d/Kalad/common/guilds/khiraa/dk/spells/kfoul.c
 * Purpose    : The spell that will make all food and drink spoil.
 * Located    : Death Knight spell
 * Created By : Sarr  17.Mar.97
 * Modified By: 
 *   Sarr 2.March.98 (updates)
 */

#define IS_DK_FOULED_FOOD    "_is_dk_fouled_food"

void
kfoul_conc(object caster, object *targets, string arg)
{
    tell_object(caster,"You weave your hands in intricate patterns "+
    "as a rancid, black aura begins to form around them.\n");
    tell_room(E(caster),QCTNAME(caster)+" weaves "+HIS(caster)+" hands "+
    "in intricate patterns as a rancid, black aura begins to form "+
    "around them.\n",caster);
}

void
do_spell_kfoul(object caster, object *targets)
{
    int i,a,amount;
    object *all,player,rot;
    string ar;

    all = deep_inventory(E(caster));

    seteuid(getuid());

    tell_room(E(caster),"A black aura surrounds "+QTNAME(caster)+".\n",
    caster);
    tell_object(caster,"A black aura surrounds you.\n");

    for (i=0;i<sizeof(all);i++)
    {
        if( function_exists("create_food",all[i]) && 
        !all[i]->query_prop(IS_DK_FOULED_FOOD) && 
        !function_exists("create_leftover",all[i])) 
        {
            player = E(all[i]);
            amount = all[i]->num_heap();
            if(amount > 1)
                ar = "are";
            else
                ar = "is";
            if(living(player))
            {
                tell_object(player,"You're "+all[i]->short()+" "+ar+" fouled "+
                "by the black aura!\n");
                tell_room(E(player),QCTNAME(player)+"'s "+all[i]->short()+ 
                " "+ar+" fouled by the black aura!\n",player);
            }
            if(player->query_prop(ROOM_I_IS))
            {
                tell_room(player,"The "+all[i]->short()+" "+ar+" fouled by "+
                "the black aura!\n");
            }
            rot = clone_object(DK_DIR+"obj/fouled_food");
            rot->set_short("rotting "+all[i]->singular_short());
            rot->set_long(all[i]->long()+"\nIt has been fouled.\n");
            rot->set_name(all[i]->query_name());
            rot->set_pshort("rotting "+all[i]->plural_short());
            rot->set_amount(all[i]->query_amount());
            rot->add_prop(OBJ_I_WEIGHT,all[i]->query_prop(OBJ_I_WEIGHT));
            rot->add_prop(OBJ_I_VOLUME,all[i]->query_prop(OBJ_I_VOLUME));
            rot->set_heap_size(amount);
            all[i]->remove_object();
            rot->move(player);
            rot->add_prop(IS_DK_FOULED_FOOD,1);
        }
        if(objectp(all[i]) && function_exists("create_drink",all[i]) &&
           !all[i]->query_prop(IS_DK_FOULED_FOOD))
        {
            player = E(all[i]);
            amount = all[i]->num_heap();
            if(amount > 1)
                ar = "are";
            else
                ar = "is";
            if(living(player))
            {
                tell_object(player,"You're "+all[i]->short()+" "+ar+" fouled "+
                "by the black aura!\n");
                tell_room(E(player),QCTNAME(player)+"'s "+all[i]->short()+ 
                " "+ar+" fouled by the black aura!\n",player);
            }
            if(player->query_prop(ROOM_I_IS))
            {
                tell_room(player,"The "+all[i]->short()+" "+ar+" fouled by "+
                "the black aura!\n");
            }
            rot = clone_object(DK_DIR+"obj/fouled_drink");
            rot->set_short("fouled "+all[i]->singular_short());
            rot->set_name(all[i]->query_name());
            rot->set_long(all[i]->long()+"\nIt has been fouled.\n");
            rot->set_pshort("rotting "+all[i]->plural_short());
            rot->set_soft_amount(all[i]->query_soft_amount());
            rot->set_alco_amount(all[i]->query_alco_amount());
            rot->add_prop(OBJ_I_WEIGHT,all[i]->query_prop(OBJ_I_WEIGHT));
            rot->add_prop(OBJ_I_VOLUME,all[i]->query_prop(OBJ_I_VOLUME));
            rot->set_heap_size(amount);
            all[i]->remove_object();
            rot->move(player);
            rot->add_prop(IS_DK_FOULED_FOOD,1);
         }   
    }
}

int
create_spell_kfoul(object caster, object *targets, string arg)
{
    if(!check_ok_cast(caster))
        return 1;

    set_spell_element(SS_ELEMENT_DEATH,10);
    set_spell_form(SS_FORM_TRANSMUTATION,10);
    set_spell_time(5);
    set_spell_conc_message(kfoul_conc);
    set_spell_mana(35);
    set_spell_ingredients(({"heart"}));
    set_spell_effect(do_spell_kfoul);
    set_spell_task(TASK_ROUTINE);
    set_spell_stationary(0);
    return 0;
}
