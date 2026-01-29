/* The Khiraa Death Knight Specials      */
/* By Sarr of Kalad   15.Mar.96          */

/* Whirlwind attack */

void bash_enemy(object me,object enemy);

public int
do_whirlwind(string target)
{
    int pen_value,
        skill_value,
        hit_value;

    mixed *hitres;

    object enemy,
           *enemys,
           first_sword,
           second_sword,
           single_sword,
           r_head;
    string my_hurt_desc,
           e_hurt_desc,
           o_hurt_desc;

    NF("Whirlwind who?\n");
    if(!target)
    {
        enemy = TP->query_attack();
        if(!objectp(enemy))
            return 0;
    }
    else
    {  
        enemys = parse_this(target,"[the] %l");
        if(!sizeof(enemys))
            return 0;
        NF("You can only attack one enemy at a time!\n");
        if(sizeof(enemys) > 1)
            return 0;
        enemy = enemys[0];
    }

    NF("You have been disgraced, and are not allowed to do this.\n");
    if(TP->query_guild_order() == -1)
        return 0;
    NF("You need more time to prepare for this maneuver.\n");
    if(member_array(TP,whirlers) != -1)
        return 0;

    first_sword = TP->query_weapon(W_RIGHT);
    second_sword = TP->query_weapon(W_LEFT);

    NF("You are not wielding at least one sword!\n");
    if(!objectp(first_sword) && !objectp(second_sword))
    {
        first_sword = TP->query_weapon(W_BOTH);
        if(!objectp(first_sword))
            return 0;
    }
    if( first_sword->query_wt() != W_SWORD || 
          second_sword->query_wt() != W_SWORD )
        return 0;
    if(!objectp(first_sword) || !objectp(second_sword) )
    {
        if(!objectp(first_sword))
            single_sword = second_sword;
        else
            single_sword = first_sword;
        pen_value = (single_sword->query_pen());
        skill_value = TP->query_skill(SS_WHIRLWIND);
        hit_value = TP->query_sword->query_hit();
        hit_value = ftoi(itof(hit_value) * 1.5);
    }
    else
    {
        pen_value = (first_sword->query_pen() + second_sword->query_pen()) / 2;
        skill_value = TP->query_skill(SS_WHIRLWIND);
        hit_value = MAX(first_sword->query_hit(),second_sword->query_hit());
        hit_value = ftoi(itof(hit_value) * 1.5);
    }

    NF("You do not know how to do this attack at all.\n");
    if(!skill_value)
        return 0;

    NF("You feel that attacking this individual will lead to an untimely "+
    "demise.\n");
    if(!F_DARE_ATTACK(TP,enemy))
        return 0;
        
    if(stringp(enemy->query_prop(OBJ_M_NO_ATTACK)))         
        NF(enemy->query_prop(OBJ_M_NO_ATTACK));
    else
        NF("This being is protected by magical forces.\n");
    if(enemy->query_prop(OBJ_M_NO_ATTACK))
        return 0;
  
    if(stringp(E(TP)->query_prop(ROOM_M_NO_ATTACK)))
        NF(E(TP)->query_prop(ROOM_M_NO_ATTACK));
    else
        NF("This room is a no-attack zone.\n");
    if(E(TP)->query_prop(ROOM_M_NO_ATTACK))
        return 0;
    if(E(TP)->query_prop(OBJ_M_NO_ATTACK))
        return 0;

    NF("You are too stunned to do this.\n");
    if(TP->query_prop(LIVE_I_STUNNED))
        return 0;
    if(TP->query_prop(LIVE_I_ATTACK_DELAY))
        return 0;

    if(TP->query_attack() != enemy)
        TP->attack_object(enemy);

    pen_value = F_PENMOD(pen_value * 2, skill_value);

    if(TP->query_combat_object()->cb_tohit(-1, hit_value, enemy) != 1)
        pen_value = -1;

    hitres = enemy->hit_me(pen_value,W_SLASH,TP,-1);

    my_hurt_desc = "but miss "+HIM(enemy)+" as "+HE(enemy)+" dodges away.\n";
    e_hurt_desc  = "but misses you as you quickly dodge away.\n";
    o_hurt_desc  = "but misses "+HIM(enemy)+" as "+HE(enemy)+" dodges away.\n";

    switch(hitres[0])
    {
        case -1:
            break;
        case 0..4:
            my_hurt_desc = "slightly scratching "+HIM(enemy)+".\n";
            e_hurt_desc = "slightly scratching you.\n";
            o_hurt_desc = my_hurt_desc;
            break;
        case 5..9:
            my_hurt_desc = "slicing "+HIM(enemy)+" in many places.\n";
            e_hurt_desc = "slicing you in many places.\n";
            o_hurt_desc = my_hurt_desc;
            break;
        case 10..19:
            my_hurt_desc = "slashing "+HIM(enemy)+" badly in many places.\n";
            e_hurt_desc = "slashing you badly in many places.\n";
            o_hurt_desc = my_hurt_desc;
            break;
        case 20..29:
            my_hurt_desc = "hacking deep wounds into "+HIS(enemy)+" body.\n";
            e_hurt_desc = "hacking deep wounds into your body.\n";
            o_hurt_desc = my_hurt_desc;
            break;
        case 30..49:
            my_hurt_desc = "shredding "+HIM(enemy)+" to pieces with "+
            "unrelenting zeal.\n";
            e_hurt_desc = "shredding you to pieces with unrelenting "+
            "zeal.\n";
            o_hurt_desc = my_hurt_desc;
            break;
        case 50..69:
            my_hurt_desc = "unmercifully hacking "+HIS(enemy)+" body "+
            "apart like the ruthless butcher you are.\n";
            e_hurt_desc = "unmercifully hacking your body apart like "+
            "a ruthless butcher.\n";
            o_hurt_desc = "unmercifully hacking "+HIS(enemy)+" body "+
            "apart like a ruthless butcher.\n";
            break;
        case 70..80:
            my_hurt_desc = "shredding and hacking "+HIM(enemy)+" "+
            "apart as blood flies everywhere.\n";
            e_hurt_desc = "shredding and hacking you apart as "+
            "your blood flies everywhere.\n";
            o_hurt_desc = my_hurt_desc;
        default:
            my_hurt_desc = "slaughtering "+HIM(enemy)+" like "+
            "a butcher serving up a carnal feast of "+
            enemy->query_race_name()+" meat.\n";
            e_hurt_desc = "slaughtering you like a butcher preparing "+
            "to serve you as the main course.\n";
            o_hurt_desc = my_hurt_desc;
    }
    if(objectp(single_sword))
    {
      tell_object(TP,"You leap into the air with your "+single_sword->short()+
        " flashing in wild arcs as you come crashing down upon "+
        enemy->query_the_name(TP)+", "+my_hurt_desc);

        tell_object(enemy,TP->query_The_name(enemy)+" leaps into the "+
        "air with "+HIS(TP)+" "+single_sword->short()+" flashing in wild "+
        "arcs as "+HE(TP)+" comes crashing down upon you, "+e_hurt_desc);

        TP->tell_watcher(QCTNAME(TP)+" leaps into the air with "+HIS(TP)+
        " "+single_sword->short()+" flashing in wild arcs as "+HE(TP)+
        " comes crashing down upon "+QTNAME(enemy)+", "+o_hurt_desc,
        enemy);
    }
    else
    {
    TP->catch_msg("You leap into the air and come crashing down on "+
    enemy->query_the_name(TP)+" with your swords spinning in a deadly swirl, "+
    my_hurt_desc);

    enemy->catch_msg(TP->query_The_name(enemy)+" leaps into the air and comes crashing "+
    "down on you with "+HIS(TP)+" swords spinning in a deadly swirl, "+
    e_hurt_desc);

    TP->tell_watcher(QCTNAME(TP)+" leaps into the air and comes crashing "+
    "down on "+QTNAME(enemy)+" with "+HIS(TP)+" swords spinning in a "+
    "deadly swirl, "+o_hurt_desc,enemy);
    }

    if(enemy->query_hp() <= 0 && !enemy->query_prop(LIVE_I_NO_CORPSE) 
       && !enemy->query_prop(LIVE_I_NO_BODY) )
    {
        setuid();
        seteuid(getuid());

        r_head = clone_object("/std/leftover");
        r_head->leftover_init("head",enemy->query_race_name());

        tell_object(enemy,"You're head falls off and to the ground.\n");
        tell_object(TP,C(HIS(enemy))+" head falls off and rolls to "+
        "your feet.\n");
        tell_room(E(TP),C(HIS(enemy))+" head falls off and rolls to "+
        QTNAME(TP)+"'s feet.\n",({TP,enemy}));
        r_head->move(E(TP));
    }

    if(enemy->query_hp() <= 0)
        enemy->do_die(TP);

    whirlers += ({ TP });
    set_alarm(compute_speed_to_round(TP,WHIRLWIND_WAIT_TIME),
        0.0,"reset_whirlwind",TP);
    return 1;
}

void
reset_whirlwind(object ob)
{
    whirlers -= ({ob});
    tell_object(ob,"\nYou feel ready to perform another whirlwind.\n");
}

/* Stun Bash attack */

public int
do_stunbash(string target)
{
    object enemy,
           *enemys;

    NF("Stunbash who?\n");
    if(!target)
    {
        enemy = TP->query_attack();
        if(!objectp(enemy))
            return 0;
    }
    else
    {  
        enemys = parse_this(target,"[the] %l");
        if(!sizeof(enemys))
            return 0;
        NF("You can only attack one enemy at a time!\n");
        if(sizeof(enemys) > 1)
            return 0;
        enemy = enemys[0];
    }

    NF("You are disgraced, and are not able to do this attack.\n");
    if(TP->query_guild_order() == -1)
        return 0;

    if(stringp(enemy->query_prop(OBJ_M_NO_ATTACK)))         
        NF(enemy->query_prop(OBJ_M_NO_ATTACK));
    else
        NF("This being is protected by magical forces.\n");
    if(enemy->query_prop(OBJ_M_NO_ATTACK))
        return 0;
  
    if(stringp(E(TP)->query_prop(ROOM_M_NO_ATTACK)))
        NF(E(TP)->query_prop(ROOM_M_NO_ATTACK));
    else
        NF("This room is a no-attack zone.\n");
    if(E(TP)->query_prop(ROOM_M_NO_ATTACK))
        return 0;
    if(E(TP)->query_prop(OBJ_M_NO_ATTACK))
        return 0;

    NF("You feel that attacking this individual will lead to an untimely "+
    "demise.\n");
    if(!F_DARE_ATTACK(TP,enemy))
        return 0;

    NF("You are too stunned to concentrate.\n");
    if(TP->query_prop(LIVE_I_STUNNED))
        return 0;
    if(TP->query_prop(LIVE_I_ATTACK_DELAY))
        return 0;

    NF("You are already preparing to bash someone.\n");
    if(member_array(TP,bashers) != -1)
        return 0;
    TP->catch_msg("You start to look for a weakness in "+QTNAME(enemy)+
    "'s defense to exploit with a stun bash.\n");
set_alarm(compute_speed_to_round(TP,BASH_WAIT_TIME),0.0,&bash_enemy(TP,enemy));
    bashers += ({TP});
    return 1;
}

public void
bash_enemy(object me, object enemy)
{
    int paralyz_time, chance;
    string my_hurt_desc,
           e_hurt_desc,
           o_hurt_desc,
           a_desc;
    object paralyz_ob;

    if (!objectp(me))
        return;

    if(me->query_prop(LIVE_I_STUNNED) ||
       me->query_prop(LIVE_I_ATTACK_DELAY))
    {
        tell_object(me,"You are too stunned to concentrate.\n");
        bashers -= ({me});
        return;
    }    

    if(!present(enemy,E(me)))
    {
        tell_object(me,"Your enemy is no longer in the room.\n");
        bashers -= ({me});
        return;
    }

    if(me->query_attack() != enemy)
        me->attack_object(enemy);

    my_hurt_desc = "but bounce harmlessly off "+HIM(enemy);
    e_hurt_desc = "but bounces harmlessly off you";
    o_hurt_desc = "but bounces harmlessly off "+HIM(enemy);

    paralyz_time = random(25) + 6;
    chance = me->query_skill(SS_BASHSTUN) / 2;

    if((random(100) + 1) <= chance && !present("knightstun",enemy))
    {
        setuid();
        seteuid(getuid());
        paralyz_ob = clone_object(DK_DIR(obj/knightstun));        
        switch(paralyz_time)
        {
            case 1..6:
                my_hurt_desc = "slightly dazing "+HIM(enemy)+".\n";
                e_hurt_desc = "slightly dazing you.\n";
                o_hurt_desc = my_hurt_desc;
            break;
            case 7..10:
                my_hurt_desc = "somewhat numbing "+HIM(enemy)+".\n";
                e_hurt_desc = "somewhat numbing "+HIM(enemy)+".\n";
                o_hurt_desc = my_hurt_desc;
            break;
            case 11..15:
                my_hurt_desc = "leaving "+HIM(enemy)+" stunned.\n";
                e_hurt_desc = "leaving you stunned!\n";
                o_hurt_desc = my_hurt_desc;
            break;
            case 16..20:
                my_hurt_desc = "leaving "+HIM(enemy)+" greatly "+
                "dazed and confused.\n";
                e_hurt_desc = "leaving you greatly dazed and "+
                "confused.\n";
                o_hurt_desc = my_hurt_desc;
            break;
            case 21..25:
                my_hurt_desc = "leaving "+HIM(enemy)+" paralyzed "+
                "on the ground.\n";
                e_hurt_desc = "leaving you paralyzed on the ground.\n";
                o_hurt_desc = my_hurt_desc;
            break;
            default:
                my_hurt_desc = "rendering "+HIM(enemy)+" nearly "+
                "unconscious.\n";
                e_hurt_desc = "rendering you nearly unconscious.\n";
                o_hurt_desc = my_hurt_desc;
            }
        paralyz_ob->set_remove_time(paralyz_time);
        paralyz_ob->move(enemy);
        enemy->add_attack_delay(paralyz_time);
    }
    else
    {
        my_hurt_desc += ".\n";
        e_hurt_desc += ".\n";
        o_hurt_desc += ".\n";
    }

    if(me->query_armour(A_R_ARM) ||
       me->query_armour(A_L_ARM))
        a_desc = "armoured";
    else
        a_desc = "bare";

    me->catch_msg("Seeing an opportunity, you quickly smash your "+
    a_desc+" shoulder into "+enemy->query_the_name(me)+"'s body, "+my_hurt_desc);

    enemy->catch_msg(me->query_The_name(enemy)+" suddenly smashes "+HIS(me)+" "+
    a_desc+" shoulder into your body, "+e_hurt_desc);

    me->tell_watcher(QCTNAME(me)+" suddenly smashes "+HIS(me)+" "+
    a_desc+" shoulder into "+QTNAME(enemy)+"'s body, "+o_hurt_desc,
    me,enemy);
   
    bashers -= ({me});


    if(enemy->query_hp() <= 0)
        enemy->do_die(me);
}
