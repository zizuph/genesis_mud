/* created by Aridor 08/24/93 */


void
arm_me(int level)
{
    string *wep = ({}), *arm = ({});
    object tmp;
    int i;
    seteuid(getuid(this_object()));
    switch (level)
    {
    case 1:
    case 2: switch(random(6))
            {
	    case 0: wep += ({"bflance"});
                    break;
            case 1: wep += ({"bdagger"});
                    break;
            case 2: wep += ({"bhandaxe"});
                    break;
            case 3: wep += ({"/d/Krynn/neraka/obj/dr_knife"});
		    break;
	    case 4: wep += ({"/d/Krynn/neraka/obj/dr_spear"});
		    break;
	    case 5: wep += ({"bshortsword"});
	            break;
            }
            break;
    case 3:
    case 4: switch(random(3))
            {
            case 0: wep += ({"/d/Krynn/neraka/obj/dr_stsword"});
                    break;
            case 1: wep += ({"bmace"});
                    break;
	    case 2: wep += ({"/d/Krynn/neraka/obj/dr_sword"});
		    break;
            }
            break;
    case 5:
    case 6: switch(random(3))
	    {
	    case 0: wep += ({"bsabre"});
	    	    break;
	    case 1: wep += ({"/d/Krynn/neraka/obj/dr_axe"});
		    break;
	    case 2: wep += ({"/d/Krynn/neraka/obj/dr_sword"});
		    break;
	    }
            break;
    case 7:
    case 8: wep += ({"bsword"});
            break;
    case 9:
    case 10: switch(random(3))
             {
	     case 0:
	     case 1: wep += ({"bbattleaxe"});
	             break;
	     case 2: switch(random(2))
	             {
		     case 0: wep += ({"bsword"});
		             break;
		     case 1: wep += ({"bsabre"});
		             break;
		     }
	             switch(random(3))
		     {
		     case 0: wep += ({"bsword"});
		             break;
		     case 1: wep += ({"bsabre"});
		             break;
		     case 2: wep += ({"bmace"});
		             break;
		     }
	             break;
	     }
             break;
    case 11:
    case 12: switch(random(3))
             { 
	     case 0:
	     case 1: wep += ({"bclaymore"});
	             break;
	     case 2: wep += ({"bsword","bsword"});
                     break;
	     }
             break;
    }
    for (i = 0; i < sizeof(wep); i++)
      {
	if (wep[i][0..0] == "/")
	  tmp = clone_object(wep[i]);
	else
	  tmp = clone_object(OBJ + wep[i]);
	if (tmp->query_prop(OBJ_I_COLORABLE))
	  tmp->set_color(color);
	tmp->move(TO);
      }

/* This was the weapon, now to the armour...*/    

    switch(level)
    {
    case 1:
    case 2: arm += ({"brobe"});
            switch(random(5))
            {
            case 0: arm += ({"bhelmet"});
                    break;
            case 1: arm += ({"bboots"});
                    break;
	    case 2: arm += ({"bshield"});
                    break;
            }
            break;
    case 3:
    case 4: arm += ({"barmour3"});
            switch(random(5))
            {
            case 0: arm += ({"bhelmet"});
                    break;
            case 1: arm += ({"bshield"});
                    break;
            case 2: arm += ({"bboots"});
                    break;
            }
            break;
    case 5:
    case 6: arm += ({"barmour2"});
            switch(random(5))
            {
            case 0: arm += ({"bshield"});
                    break;
            case 1: arm += ({"bleggings"});
                    break;
            case 2: arm += ({"bheavyboots"});
                    break;
	    case 3: arm += ({"blargeshield"});
                    break;
            }
            break;
    case 7:
    case 8: arm += ({"barmour1"});
            switch(random(4))
            {
            case 0: arm += ({"blargeshield"});
                    break;
            case 1: arm += ({"bleggings"});
	            break;
	    case 2: arm += ({"bshinguard"});
	            break;
	    case 3: arm += ({"bheavyboots"});
                    break;
            }
            break;
    case 9:
    case 10: arm += ({"barmour1"});
             switch(random(4))
	       {
		 case 0: arm += ({"blargeshield"});
		 case 1: arm += ({"bleggings", "bdragonhelm"});
		         break;
		 case 2: arm += ({"blargeshield"});
		 case 3: arm += ({"bshinguard", "bheavyboots"});
		         break;
	       }
             break;
    case 11: arm += ({"bdragonarm", "bshinguard", "bdragonhelm"});
             break;
    case 12: arm += ({"bdragonarm", "bshinguard","bheavyboots","bdragonhelm"});
             break;
    }
    for (i = 0; i < sizeof(arm); i++)
      {
	if (arm[i][0..0] == "/")
	  tmp = clone_object(arm[i]);
	else
	  tmp = clone_object(OBJ + arm[i]);
	tmp->move(TO);
	if (tmp->query_prop(OBJ_I_COLORABLE))
	  tmp->set_color(color);
      }

/* different armour and weapon for the different levels!*/

    command("wield all");
    command("wear all");
}

