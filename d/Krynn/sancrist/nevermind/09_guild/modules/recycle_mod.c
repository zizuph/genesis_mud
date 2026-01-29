/********************** module: Recycler **********************************
 *                        flag: 7                                         *
 **************************************************************************/

int
recycle(string str)
{
    int a, i, *count_in, *wep_loc, *arm_loc;
    object ob, reus;   
    string name;

    count_in = ({0,1,2,3,4});
    arm_loc = ({2,4,8,16,32,64,128,256,512,1024,2048,4096,8192,16384,
      32768,65536});
    wep_loc = ({512,1024,2048,4096,384}); 
    NF("You forgot to attach that module.\n");;
    if(!flag(7,0))
        return 0;
    if (!darkcheck(TP))
        return 1;
    NF("Recycle what?\n");
    if(!str)
        return 0;
    NF("You don't have a " + str + ".\n");   
    if(!(ob = P(str, TP)))
        return 0;
    if(reus = P("_reusable_parts_module_", TP))
    {
 [32m        name = reus->get_name(); [0m
        NF("You already own a " + C(name) + ". Why do you need two?\n");
        if(name != "_rpm_")
            return 0;   
    }
    NF("You cannot recycle that.\n");
 [32m    if((ob->query_prop(OBJ_M_NO_DROP)) || (ob->query_prop(OBJ_M_NO_GIVE)) || [0m
      (ob->query_prop(MAGIC_AM_MAGIC)))
        return 0;   
 [32m    NF("Coins don't give a lot material. It's better if you kept it.\n"); [0m
    if(ob->query_name() == "coin")
        return 0;
    NF("You cannot recycle worn or wielded objects.\n");
    for(i=0;i<16;i++)
        if(TP->query_armour(arm_loc[i]) == ob)
            return 0;
    NF("You cannot recycle wielded objects.\n");
    for(i=0;i<5;i++)
        if(TP->query_weapon(wep_loc[i]) == ob)
            return 0;
    NF("You are already recycling something.\n");
    if(QUERY_CALL(TP) != 0)
        return 0;

    if(flag(7,1) == -1)
        return 1;       /* Break test */

    ob->add_prop(OBJ_I_NO_DROP, 1);
    ob->set_no_show();
    ob->add_prop("_obj_i_recycling", 1);
 [32m    write("You put the " + ob->short() + " into the " [0m
      + "recycling chamber of the "
 [35m      + "gizmo and pull the lever...\nA bell rings and the shutter " [0m
      + "closes the chamber.\n");
 [33m    say(QCTNAME(TP) + " does something to " + POSSESSIVE(TP)  [0m
      + " gizmo causing a bell to ring alarmingly.\n");

 [32m    /* Lets get a random order for the messages. */ [0m

    for(i=0;i<3;i++)
    {     
        a = random(sizeof(count_in));
        if(count_in[a] != -1)   

        {        
            TP->add_prop("_recycler_msg_nr_" + i, count_in[a]);
            count_in[a] = -1;
        }
        else
            i--;
    }
    SET_CALL(TP, 1);
    return 1;
}

int
recycle_2(string str)                         
{
    string *msg = ({"your gizmo produces a contented 'BURP'.\n", "hear "
      + "a loud 'CRUNCH'.\n", "hear a noisy 'MUNCH ... MUNCH ... MUNCH'.\n" 
      ,"a light blinks indicating that something has just been considerably "
      + "reduced in size.\n"
 [35m      ,"the Recycler spits some unusable tiny pieces to the ground.\n"}) [0m

    ,*tel_msg = ({" and something makes 'BURP'.\n", " and something makes " +
      "'CRUNCH'.\n", " and something makes 'MUNCH ... MUNCH ... MUNCH'.\n",
      ".\n", ".\n"})
    , *often = ({"second", "third", "last"});

    int call, msg_nr;

    /* We are using the same syntax for the PersonalCleanlinessModule */
    if(QUERY_WASH(TP) > 0)
    {
        NF("Pull what?\n");     
        return wash_me(str);
    }

    NF("You forgot to attach that module.\n");
    if(!flag(7,0))
        return 0;
    NF("Pull what?\n");   
    if(str != "lever")
        return 0;

    call = QUERY_CALL(TP);
    NF("The lever of the Recycler is blocked.\n");
    if(call < 1 || call > 3)
        return 0;
    msg_nr = TP->query_prop("_recycler_msg_nr_" + (call - 1));
    TP->remove_prop("_recycler_msg_nr_" + (call - 1));
 [32m    TP->catch_msg("You pull the lever for a " + often[call - 1] + " time and " [0m
      + msg[msg_nr]);

    tell_room(E(TP), QCTNAME(TP) + " does something to " + POSSESSIVE(TP)
      + " gizmo" + tel_msg[msg_nr], TP);

    if(call == 3)
        set_alarm(4.0, -1.0, "end_recycle", TP);
    SET_CALL(TP, call + 1);
    return 1;
}

/* We want to know which materials were recycled.
 [32m * add_material() stores the information in reus_par.c [0m
 */
string        
compare_material(string adject)
{
    string *mats = ({"wood", "copper", "metal", "silver", "gold", "bronze",
      "lead", "rust", "leather", "mithril", "adamant", "steel", "iron"});
    int i;

    for(i=0;i<sizeof(mats);i++)
    {
        if((adject == mats[i]) || (adject == mats[i] + "en") || 
          (adject == mats[i] + "y") || (adject == mats[i] + "n"))
            return mats[i];

        if(adject == "metallic")
            return "metal";
        if(adject == "furry")
            return "fur";
    }
    return "none";
}

void
 [32mget_material(mixed adject, object rpm) [0m
{
    mixed result;
    int i;

    if(stringp(adject))
    {
        if((result = compare_material(adject)) != "none")
            rpm->add_material(result);
        return;
    }
    for(i=0;i<sizeof(adject);i++)
    {   
        if((result = compare_material(adject[i])) != "none")
            rpm->add_material(result);

    }
}

void
end_recycle(object player)
{
    object rpmod, *inv, ob;
    int i;

    SET_CALL(player, 0);
    if(!(rpmod = present("_reusable_parts_module_", player)))
    {
 [32m        setuid(); seteuid(getuid()); [0m
        rpmod = clone_object(GOBJ + "reus_par");
        rpmod->move(player);
    }

    inv = all_inventory(player);
    for(i=0;i<sizeof(inv);i++)
        if(inv[i]->query_prop("_obj_i_recycling"))
            ob = inv[i];

    rpmod->add_prop(OBJ_I_WEIGHT, (rpmod->query_prop(OBJ_I_WEIGHT)) 
      + (ob->query_prop(OBJ_I_WEIGHT))/2);

    rpmod->add_volume((ob->query_prop(OBJ_I_VOLUME))/50);
 [32m    get_material(ob->query_adj(), rpmod); [0m
 [32m    get_material(explode((ob->short()), " "), rpmod); [0m
    rpmod->check_complete(player);
    ob->remove_object();
    player->catch_msg("You are ready to recycle again.\n");
}

 [32m/* Nobody wants to get rid of a half complete ReusablePartsModule [0m
 * But anyway...
 */

int
flush(string str)
{
    object rpm, gizmo;

    NF("You forgot to attach that module.\n");;
    if(!flag(7,0))
        return 0;
    NF("Flush what?\n");
    if(str != "recycler")
        return 0;
    NF("There is nothing inside the recycler. Yet...\n");

    if(!(rpm = P("_rpm_", TP)))
        return 0;
    NF("You'll need a waterdispenser to flush the recycler.\n");
    if(!flag(2,0))
        return 0;   
    NF("Your waterdispenser is empty.\n");
    gizmo = find_gizmo(TP);
    if(gizmo->check_water() < 1)
        return 0;
    gizmo->reduce_water();
 [32m    write("You pull the handle.\n"); [0m
 [33m    say(QCTNAME(TP) + " does something to " + POSSESSIVE(TP) + " gizmo.\n"); [0m
    set_alarm(3.0, -1.0, "flush_2", rpm, TP);
    return 1;
}

void
flush_2(object rpm, object player)
{
    object junk;

    player->catch_msg("There is a sound like water running down a "   
      + "drain and the recycler ejects something in a splash of "
      + "water.\n");

    tell_room(E(player), "There is a sound like water running down "
      + "a drain and something falls from " + QTNAME(player)
      + " in a splash of water.\n", player);

 [32m    setuid();seteuid(getuid()); [0m
    junk = clone_object(GOBJ + "junk");
    junk->add_adj("wet");
    junk->set_short("wet gnomish junk");
    junk->set_long("This is a huge junk of different materials with "
      + "no recognisable purpose or design. I guess only a gnome "
      + "could have produced that.\nIt's very wet.\n");
    junk->add_prop(OBJ_I_WEIGHT, rpm->query_prop(OBJ_I_WEIGHT));
    junk->add_prop(OBJ_I_VOLUME, rpm->query_prop(OBJ_I_VOLUME));
    junk->move(E(player));

    rpm->remove_object();
}

