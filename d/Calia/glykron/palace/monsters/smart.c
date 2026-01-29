inherit "/std/monster";

#define TRUTH 0
#define PARAMS RETURN_VALUE
#define BODY_LIST 2

#define HEAD 0
#define BODY 1

mapping logic;

mixed call_atom(string atom_name, status truth, mixed params)
{
    mixed return_value;
    logic[atom_name][STATUS] = status;
    return_value = status ? call_other(atom_name, params) : 0;
    for (i = 0; i < sizeof(logic[atom_name][BODY_LIST]); ++i)
	call_rule(logic[atom_name][BODY_LIST][i]);
    return return_value;
}

void call_rule(string rule_name)
{
    int truth;
    truth = 0;
    for (i = 0; i < sizeof(logic[rule_name][BODY]); ++i)
    {
	mixed *literal = logic[rule_name][BODY];
	truth &= literal[1] == logic[literal[0]][STATUS];
	params += ({ logic[literal[0]][RETURN_VALUE] });
    }
    if (truth)
    {
	mixed *literal = logic[rule_name][HEAD];
	call_atom(literal[0], literal[1], params);
    }
}

void add_atom(string atom_name, status truth)
{
    logic[atom_name] = ({ truth, 0, ({ }) });
    call_atom(atom_name, params);
}

void add_rule(string rule_name, string head, string *body)
{
    logic[rule_name] = ({ head, body });
    for (i = 0; i < sizeof(body); ++i)
	logic[body[i][1]][BODY_LIST] += ({ rule_name, i });
    call_rule(rule_name);
}
