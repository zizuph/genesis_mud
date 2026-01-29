
/*
     Cadet armoury.  

     A room for cadets to donate stuff. It contains a number of racks. 

     Coded by Maniac@Genesis, 6/2/98 
     Updated by Maniac 9/3/99
 */ 

inherit "/std/room"; 

#include <stdproperties.h>
#include <macros.h> 
#include <files.h>
#include <config.h>
#include <cmdparse.h>
#include <composite.h>
#include <language.h>
#include "cadet.h"


object *racks; 
string racks_desc; 
int automatic_racks_desc_update; 


int
gc_query_private_room()
{
    return 1;
}


string
a_short(object ob)
{
    return LANG_ASHORT(ob); 
}


string
query_updated_racks_desc()
{
    if (!sizeof(racks))
        return "There are currently no racks here."; 

    return ("The following racks occupy the walls: " +
            COMPOSITE_WORDS(map(racks, a_short)) + "."); 
}


string
query_racks_desc()
{
    return racks_desc + "\n"; 
}


string
long_desc()
{
    return ("The Cadets' armoury. This is a good place to " + 
            "collect cloaks, donate daggers, stack slings and " +
            "archive arrows in the provided racks. " + racks_desc + 
            " There is a metal sign here.\n");
}


void
create_room()
{
    string sign_text = 
         ("When any item of monetary value " +
          "(except coins) is put in one of the racks here by " +
          "a cadet, the donator " +
          "is credited with a number of rack points, provided " +
          "s/he does not have a bad reputation (see \"help cadet " +
          "reputation\"). The higher " +
          "the item's value, the more rack points are awarded. " + 
          "When the item is taken from a rack, the borrower will have " +
          "his/her points total debited by the same amount. " +
          "You may \"donate <item(s)>\" to automatically put an " +
          "item or items in the correct rack. When referring to " +
          "a rack you may use just the first three letters " +
          "of its adjective e.g. \"examine swo rack\", " +  
          "\"get pack from rec rack\". " + 
          "Rack security is enforced by a rule that no-one may " +
          "take an item from a rack if it is worth more than his/her " +
          "points total. Keep in mind that the contents of the racks " +
          "will not survive Armageddon unless you carry them " +
          "with you into the new world. " +
          "During Armageddon you won't get any " +
          "rack points for donating an item. Non-recoverable items " + 
          "cost no rack points to take during Armageddon, but " + 
          "recoverable items cost almost the normal amount. Shaking " + 
          "a rack during Armageddon will cause all non-recoverable " + 
          "items to fall out of it. " + 
          "Your rack points are always remembered after Armageddon " +
          "and there is no limit to the number that you can have. " +
          "However your exact points total is something for only " +
          "Xorfin to know! " +
          "Note that the racks have limits on the amount of " +
          "equipment they can hold (you may find out what their " +
          "limits are by appraising them). The least valuable " +
          "items are removed if a limit is exceeded. The " +
          "method for calculating value varies depending on the " +
          "type of the item. Even if an item is immediately " +
          "removed, you still receive points if it is of any " +
          "value. You will NOT receive rack points for any items " +
          "that are simply dropped in this room.\n"); 

    set_short("Cadets' armoury");  
    set_long(long_desc); 

    add_item(({"sign", "metal sign"}), sign_text); 

    add_cmd_item(({"sign", "metal sign"}), "read", sign_text); 

    add_item(({"wall", "walls"}), query_racks_desc); 

    add_prop(ROOM_I_INSIDE, 1); 
    add_prop(ROOM_I_NO_CLEANUP, 1); 
    add_prop(ROOM_I_HIDE, 35); 
    add_prop(ROOM_M_NO_STEAL, "The rack guard glares at you " +
           "ominously, putting you off any attempt to steal.\n"); 
    add_exit(GC_STARTROOM, "east");  

    racks = ({ }); 

    automatic_racks_desc_update = 0; 
    clone_object(GC_RACK_DIR+"misc_rack")->move(this_object()); 
    clone_object(GC_RACK_DIR+"torch_rack")->move(this_object()); 
    clone_object(GC_RACK_DIR+"receptacle_rack")->move(this_object()); 
    clone_object(GC_RACK_DIR+"food_rack")->move(this_object()); 
    clone_object(GC_RACK_DIR+"drink_rack")->move(this_object()); 
    clone_object(GC_RACK_DIR+"shield_rack")->move(this_object()); 
    clone_object(GC_RACK_DIR+"helm_rack")->move(this_object()); 
    clone_object(GC_RACK_DIR+"greaves_rack")->move(this_object()); 
    clone_object(GC_RACK_DIR+"cloak_rack")->move(this_object()); 
    clone_object(GC_RACK_DIR+"bracers_rack")->move(this_object()); 
    clone_object(GC_RACK_DIR+"body-armour_rack")->move(this_object()); 
    clone_object(GC_RACK_DIR+"sword_rack")->move(this_object()); 
    clone_object(GC_RACK_DIR+"polearm_rack")->move(this_object()); 
    clone_object(GC_RACK_DIR+"knife_rack")->move(this_object()); 
    clone_object(GC_RACK_DIR+"club_rack")->move(this_object()); 
    clone_object(GC_RACK_DIR+"axe_rack")->move(this_object());
    racks_desc = query_updated_racks_desc();  
    automatic_racks_desc_update = 1; 
}


void
register_cadet_rack(object ob)
{
    racks -= ({ 0 }); 
    racks = ({ ob }) + racks; 
    ob->set_no_show_composite(1); 
    if (automatic_racks_desc_update)
        racks_desc = query_updated_racks_desc(); 
}


void
unregister_cadet_rack(object ob)
{
    racks -= ({ 0, ob }); 
    ob->unset_no_show_composite();
    if (automatic_racks_desc_update) 
        racks_desc = query_updated_racks_desc(); 
}


/* 
 * Function:       donate_one_object 
 * Description:    Donates an object to the guild racks. Returns 1 
 *                 if successfully donated, 0 otherwise. 
 * 
 */ 
varargs int 
donate_one_object(object tp, object ob, string msg) 
{
    int i; 
    object target_rack; 

    i = 0; 
    while (i < sizeof(racks)) {  
        if (racks[i]->fits(ob)) { 
            target_rack = racks[i]; 
            break; 
        } 
        i++; 
    } 

    if (!objectp(target_rack)) { 
        if (!stringp(msg)) 
            tell_object(tp, "You cannot find a rack where " + 
                        LANG_THESHORT(ob) + " fits.\n"); 
        return 0; 
    } 
    else if (ob->query_keep()) { 
        if (!stringp(msg)) 
            tell_object(tp, "You will have to unkeep " + 
                        LANG_THESHORT(ob) + " first.\n"); 
        return 0; 
    } 
    else if (ob->move(target_rack)) { 
        if (!stringp(msg)) 
            tell_object(tp, "For some reason you could not put " + 
                            LANG_THESHORT(ob) + " in " + 
                            LANG_THESHORT(target_rack) + ".\n"); 
        return 0; 
    } 
    else { 
        if (stringp(msg)) { 
            tell_room(this_object(), msg); 
            return 1; 
        } 
        tell_object(tp, "You put " + 
                  LANG_THESHORT(ob) + " in " + 
                  LANG_THESHORT(target_rack) + ".\n"); 
        tell_room(this_object(), QCTNAME(tp) + " puts " + 
                  LANG_ASHORT(ob) + " in " + 
                  LANG_THESHORT(target_rack) + ".\n", tp); 
        return 1; 
    } 
}


int
do_donate(string str)
{
    object *donating, tp; 

    notify_fail("Donate what?\n"); 

    if (!stringp(str) || !strlen(str)) 
        return 0; 

    tp = this_player(); 

    donating = FIND_STR_IN_OBJECT(str, tp);  
    if (!sizeof(donating)) 
        return 0; 

    map(donating, &donate_one_object(tp,));  
    return 1; 
}


int
do_shake(string str)
{
    object *trg; 

    notify_fail("Shake what?\n"); 

    if (!stringp(str) || !strlen(str)) 
        return 0; 

    trg = FIND_STR_IN_ARR(str, racks);  
    if (!sizeof(trg)) 
        return 0; 

    if (sizeof(trg) > 1) { 
        write("You can't shake more than one rack at once!\n");  
        return 1; 
    } 

    write("You shake " + LANG_THESHORT(trg[0]) + ".\n"); 
    say(QCTNAME(this_player()) + " shakes " + LANG_THESHORT(trg[0]) + ".\n"); 
    trg[0]->expel_non_recoverable_objects();  

    return 1; 
}


void
init()
{
    ::init(); 
    add_action(do_donate, "donate"); 
    add_action(do_shake, "shake"); 
}

