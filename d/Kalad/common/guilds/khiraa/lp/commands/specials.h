/* The Lich Priesthood Specials      */
/* By Sarr of Kalad   5.Apr.97          */

/* Gouge  */

void gouge_enemy(object me,object enemy,int pen_value,object weapon, int i);


void
direct_reset(object me)
{
    tell_object(me,"\n You can now direct and move behind again.\n\n");
    me->remove_prop(DIRECT_WAIT);
}

public int
valid(object enemy, object me)
{
    if(!present(enemy,E(me)))
        return 0;
    if(enemy->query_attack() != me)
        return 0;
    return 1;
}


public int
do_direct(string str)
{
    object *targets,knight,*emys;
    targets = parse_this(str,"[the] %l");
    NF("You need more time to prepare.\n");
    if(TP->query_prop(DIRECT_WAIT))
        return 0;
    if(sizeof(targets))
        knight = targets[0];
    NF("Direct which death knight in front of you?\n");
    if(!objectp(knight))
        return 0;
    NF("That is not a death knight.\n");
    if(!IS_DK(knight))
        return 0;
    emys = filter(TP->query_enemy(-1),&valid(,TP));    
    NF("You are not being attacked by anyone.\n");
    if(!sizeof(emys))
        return 0;
    write("You direct "+knight->query_the_name(TP)+" in front of you "+
    "and begin to manuever your way behind "+HIM(knight)+".\n");
    tell_room(E(TP),QCTNAME(TP)+" directs "+QTNAME(knight)+" in front of "+HIM(TP)+
    " and begins to manuever "+HIS(TP)+" way behind "+HIM(knight)+".\n",({TP,knight}));
    tell_object(knight,TP->query_The_name(knight)+" directs you in front "+
    "of "+HIM(TP)+" and begins to manuever behind you. You now face "+
    HIS(TP)+" enemies.\n");
    emys->catch_msg("You now face "+QTNAME(knight)+".\n");
    emys->attack_object(knight);
set_alarm(compute_speed_to_round(TP,DIRECT_RESET_TIME),0.0,&direct_reset(TP));
    TP->add_prop(DIRECT_WAIT,1);
    return 1;
}


public int
do_gouge(string target)
{
    int pen_value,
        skill_value,
        pen_weapon,
        hit_value;

    object enemy,
           *enemys;
    object *weapons,weapon;

    NF("Gouge who?\n");
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

    NF("You don't have a weapon wielded!\n");
    weapons = TP->query_weapon(-1);
    if(!sizeof(weapons))
        return 0;

    weapon = weapons[0];

    NF("This weapon has no sharp edge to gouge!\n");
    if(weapon->query_wt() == W_BLUDGEON)
        return 0;

    skill_value = TP->query_skill(SS_GOUGE);
    pen_weapon = (weapon->query_pen() * 5) / 4;
    pen_value = F_PENMOD(pen_weapon,skill_value);
    hit_value = (weapon->query_hit() * 5) / 4;

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
    if( E(TP)->query_prop(ROOM_M_NO_ATTACK))
        return 0;
    if(E(TP)->query_prop(OBJ_M_NO_ATTACK))
        return 0;

    NF("You are too stunned to concentrate.\n");
    if(TP->query_prop(LIVE_I_STUNNED))
        return 0;
    if(TP->query_prop(LIVE_I_ATTACK_DELAY))
        return 0;

    NF("You are already preparing to gouge someone.\n");
    if(member_array(TP,gougers) != -1)
        return 0;

    TP->catch_msg("You start to look for a weakness in "+QTNAME(enemy)+
    "'s defense to exploit with a gouge.\n");


set_alarm(compute_speed_to_round(TP,GOUGE_WAIT_TIME),0.0,
     &gouge_enemy(TP,enemy,pen_value,weapon,hit_value));

    gougers += ({TP});
    return 1;
}

public void
gouge_enemy(object me, object enemy,int pen_value, object weapon, int hitv)
{
    string my_hurt_desc,
           e_hurt_desc,
           o_hurt_desc;

    mixed *hitres;

    if(me->query_prop(LIVE_I_STUNNED) ||
       me->query_prop(LIVE_I_ATTACK_DELAY))
    {
        tell_object(me,"You are too stunned to gouge.\n");
        gougers -= ({me});
        return;
    }    
    if(!present(enemy,E(me)))
    {
        tell_object(me,"Your enemy is no longer in the room.\n");
        gougers -= ({me});
        return;
    }
    if(me->query_attack() != enemy)
        me->attack_object(enemy);

    if(me->query_combat_object()->cb_tohit(-1, hitv, enemy) != 1)    
        pen_value = -1;
 
    hitres = enemy->hit_me(pen_value,W_SLASH,me,-1,3);

    my_hurt_desc = "just barely miss "+HIM(enemy);
    e_hurt_desc = "just barely misses you";
    o_hurt_desc = "just barely misses "+HIM(enemy);

    switch(hitres[0])
    {
        case -1:
            break;
        case 0..4:
            my_hurt_desc = "slightly scratch "+HIM(enemy);
            e_hurt_desc = "slightly scratches you";
            o_hurt_desc = "slightly scratching "+HIM(enemy);
            break;
        case 5..9:
            my_hurt_desc = "cut a small wound in "+HIM(enemy);
            e_hurt_desc = "cuts a small wound in you";
            o_hurt_desc = "cuts a small wound in "+HIM(enemy);
            break;
        case 10..19:
            my_hurt_desc = "slash a large wound in "+HIM(enemy);
            e_hurt_desc = "slashes a large wound in you";
            o_hurt_desc = "slashes a large wound in "+HIM(enemy);
            break;
        case 20..29:
            my_hurt_desc = "rip a large wound across "+HIS(enemy)+" belly";
            e_hurt_desc = "rips a large wound across your belly";
            o_hurt_desc = "rips a large wound across "+HIS(enemy)+" belly";
            break;
        case 30..49:
            my_hurt_desc = "rip a large bloody gash across "+HIS(enemy)+" belly";
            e_hurt_desc = "rips a large bloody gash across your belly";
            o_hurt_desc = "rips a large bloody gash across "+HIS(enemy)+" belly";
            break;
        case 50..69:
            my_hurt_desc = "tear open a terrible gaping wound across "+
                           HIS(enemy)+" belly";
            e_hurt_desc = "tears open a terrible gaping wound across your belly";
            o_hurt_desc = "tears open a terrible gaping wound across "+
                           HIS(enemy)+" belly";
            break;
        case 70..80:
            my_hurt_desc = "brutally shred open "+HIS(enemy)+" belly";
            e_hurt_desc = "brutally shreds open your belly";
            o_hurt_desc = "brutally shreds open "+HIS(enemy)+" belly";
        default:
            my_hurt_desc = "brutally disembowel "+HIM(enemy);
            o_hurt_desc = "brutally disembowels "+HIM(enemy);
            e_hurt_desc = "brutally disembowels you";
    }

    me->catch_msg("Seeing an opportunity, you strike out at "+
    enemy->query_the_name(me)+"'s exposed body, and "+my_hurt_desc+" with "+
    "your "+weapon->short()+"!\n");

    enemy->catch_msg(me->query_The_name(enemy)+" suddenly strikes out at your "+
    "body and "+e_hurt_desc+" with "+HIS(me)+" "+weapon->short()+"!\n");

    me->tell_watcher(QCTNAME(me)+" suddenly strikes out at "+QTNAME(enemy)+
    "'s body and "+o_hurt_desc+" with "+HIS(me)+" "+weapon->short()+
    "!\n",enemy);

    gougers -= ({me});

    if(enemy->query_hp() <= 0)
        enemy->do_die(me);
}
