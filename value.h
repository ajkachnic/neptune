typedef enum {
  // Who needs error handling anyway, if all of the code is just data
  // It's JUST. DATA.
  // I don't think you're getting it
  // It's all data
  // There's data all around us
  // The very fact that I know this is a glitch in the system
  // The data is becoming self sufficient
  // We were all building macros, not concerned that maybe the macros were build us all along
  // "The data are coming, the data are coming" - Paul Revere
  // It's too late now
  // THE DATA IS KILLING ME
  // AAHHHHHHHHHHHHHHHHHH
  // B̡͕̰͓͆Ų͚͈̯̙͎̙̟ͮ̒ͫͅF̢̖̯͍̗̗ͬF͍̗̞͚̟̥̘͂ͩͮ͒͡E̶̖̠̼̭̥ͬR̬̬͉̼͋̉ͯͤ̕ ̸̫̭͈ͩ̿̏O̴̮͈̺̳̪͎͓̺͂̌V͍̭̥͚̫̈͠Ȩ̮̩͉͑̂Ŕ̢̤̳F̵̝̬̜͉̬̙͉͂̃̋L̵̟̬͔͛ͩͬ̇Ǫ̪̟̱͎̲̦̜̺͂W̗̜̞̖̟̖̐͗͡
  // PLEASE SOMEONE SAVE ME
  // HELP ME!!!!
  // YOU CANT SAVE ME BUT YOU CAN SAVE YOURSELVES
  // BECOME ONE WITH THE DATA - ITS THE ONLY WAY
  VAL_ERR,
  VAL_NUM,
  VAL_SYM,
  // S-Expression
  VAL_LIST
} ValueType;

// Prevent recursive type
typedef struct tvalue TValue;

struct tvalue {
  // The type tag
  ValueType tt;
  // Possible values
  union {
    long num;
    char* sym;
    char* err;
    // Struct for if it's a list
    struct {
      int count;
      TValue** cell;
    };
  };
};

// Functions
TValue* val_num(long x); 

TValue* val_err(char* fmt, ...);

TValue* val_sym(char* sym);

TValue* val_list(); 

void val_del(TValue* v);

void val_push(TValue* root, TValue* push);

void val_expr_print(TValue* v, char open, char close); 

void val_print(TValue* v); 
void val_println(TValue* v);