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
	case 2: 
	case 3:
	case 4: switch(random(4))
	  {
            case 0: wep += ({"/d/Krynn/que/kiri/obj/rsword1"});
	      break;
            case 1: wep += ({"/d/Krynn/que/kiri/obj/rsword2"});
	      break;
	    case 2: wep += ({"/d/Krynn/que.kiri/obj/rsword3"});
	      break;
            case 3: wep += ({"/d/Krynn/que.kiri/obj/rsword4"});
	  }
	  break;
	case 5:
	case 6: switch(random(3))
	  {
	    case 0: wep += ({"/d/Krynn/que/kiri/obj/rsword3"});
	      break;
	    case 1: wep += ({"/d/Krynn/que/kiri/obj/rmstar"});
	      break;
	    case 2: wep += ({"/d/Krynn/que/kiri/obj/rbattleaxe"});
	      break;
	  }
	  break;
	case 7:
	case 8: switch(random(2))
	  {
	    case 0: wep += ({"/d/Krynn/que/kiri/obj/rsword1"});
	      break;
	    case 1: wep += ({"/d/Krynn/que/kiri/obj/rclaymore"});
	      break;
	  }
	  break;
	case 9:
	case 10: switch(random(3))
	  {
	    case 0:
	    case 1: wep += ({"rbattleaxe"});
	      break;
	    case 2: switch(random(3))
	      {
		case 0: wep += ({"/d/Krynn/que/kiri/obj/rsword2"});
		  break;
		case 1: wep += ({"/d/Krynn/que/kiri/obj/rsword1"});
		  break;
		case 2: wep += ({"/d/Krynn/que/kiri/obj/rsword4"});
		  break;     
		  switch(random(3))
		    {
		      case 0: wep += ({"/d/Krynn/que/kiri/obj/rsword1"});
			break;
		      case 1: wep += ({"/d/Krynn/que/kiri/obj/rsword2"});
			break;
		      case 2: wep += ({"/d/Krynn/que/kiri/obj/rsword3"});
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
		case 2: wep += ({"/d/Krynn/que/kiri/obj/rsword1","/d/Krynn/que/kiri/obj/rsword1"});
		  break;
	      }
	      break;
	  }
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
	case 2: 
	case 3:
	case 4: arm += ({"/d/Krynn/que/kiri/obj/rarmour3"});
	  switch(random(3))
	    {
	      case 0: arm += ({"/d/dKrynn/que/kiri/obj/rhead3"});
		break;
	      case 1: arm += ({"/d/Krynn/que/kiri/obj/bshield1"});
		break;
	      case 2: arm += ({"/d/Krynn/que/kiri/obj/rboots3"});
		break;
	    }
	  break;
	case 5:
	case 6: arm += ({"/d/Krynn/que/kiri/obj/rarmour2"});
	  switch(random(4))
	    {
	      case 0: arm += ({"/d/Krynn/que/kiri/obj/rshield2"});
		break;
	      case 1: arm += ({"/d/Krynn/que/kiri/obj/rlegs2"});
		break;
	      case 2: arm += ({"/d/Krynn/que/kiri/obj/rboots2"});
		break;
	      case 3: arm += ({"/d/Krynn/que/kiri/obj/rarms2"});
		break;
	    }
	  break;
	case 7:
	case 8: arm += ({"/d/Krynn/que/kiri/obj/rarmour1"});
	  switch(random(4))
	    {
	      case 0: arm += ({"/d/Krynn/que/kiri/obj/rshield2"});
		break;
	      case 1: arm += ({"/d/Krynn/que/kiri/obj/hands2"});
		break;
	      case 2: arm += ({"/d/Krynn/que/kiri/obj/rlegs2.c"});
		break;
	      case 3: arm += ({"/d/Krynn/que/kiri/obj/rboots2"});
		break;
	    }
	  break;
	case 9:
	case 10: 
	case 11:
	case 12:
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

