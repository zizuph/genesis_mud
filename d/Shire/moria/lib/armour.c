//
// armour.c
//
// Base armour used in Moria.
//

inherit "/std/armour";

mixed arm_resistance;
mixed arm_slots;
object extra_af;
int is_fullplate;

nomask void
create_armour()
{
    add_prop(OBJ_I_IS_MAGIC_ARMOUR, 1);
    arm_resistance = ({});
    arm_slots = ({});
    ::set_af(this_object());
    this_object()->create_moria_armour();
}

void
set_af(object obj)
{
    extra_af = obj;
}

void
set_at(int type)
{
    if (type == A_FULLPLATE)
    {
	::set_at(A_BODY);
	arm_slots = ({ A_BODY, A_L_ARM, A_R_ARM, A_LEGS });
	set_shield_slot(arm_slots);
	is_plate = 1;
	return;
    }
    ::set_at(type);
}

varargs void
set_arm_resistance(mixed first_arg, ...)
{
    if (intp(first_arg))
	arm_resistance = ({ first_arg }) + argv;
    else if (pointerp(first_arg))
	arm_resistance = first_arg;
}

int *
query_slots()
{
    if (is_plate || sizeof(arm_slots))
	return arm_slots + ({});
    else
	return ::query_slots();
}

varargs
add_magic_res(object who = environment())
{
    int i;
    for(i=0;i<sizeof(arm_resistance);i+=2)
    {
	add_prop(res[i], ({ res[i+1], 1 }) );
	ob->add_prop(res[i], ob->query_prop(res[i])+1);
    }
}

varargs
remove_magic_res(object who = query_worn())
{
    int i;
    for(i=0;i<sizeof(res);i+=2)
    {
	ob->add_prop(res[i], ob->query_prop(res[i])-1);
	remove_prop(res[i]);
    }
}

mixed
wear(object to)
{
    object tp=environment(to);
    add_magic_res(tp);
    return extra_af->wear(to);
}

mixed
remove(object to)
{
    object tp=query_worn();
    remove_magic_res(tp);
    return extra_af->remove(to);
}

string
wear_how(int loc)
{
    string pos;

    if (!is_plate)
	return ::wear_how(loc);

    if(!query_worn() || query_worn()==this_player())
	pos = "your";
    else
	pos = query_worn()->query_possessive();

    if(loc==A_BODY)
	return " over "+pos+" body";
    else
	return ::wear_how(loc);
}

