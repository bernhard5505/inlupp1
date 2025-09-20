#include <stdlib.h>
#include "hash_table.h"

typedef struct entry entry_t;
typedef struct hash_table ioopm_hash_table_t;

struct entry
{
  int key;       // holds the key
  char *value;   // holds the value
  entry_t *next; // points to the next entry (possibly NULL)
};

struct hash_table
{
  entry_t *buckets[17];
};

ioopm_hash_table_t *ioopm_hash_table_create()
{
  /// Allocate space for a ioopm_hash_table_t = 17 pointers to
  /// entry_t's, which will be set to NULL
  ioopm_hash_table_t *result = calloc(1, sizeof(ioopm_hash_table_t));
  return result;
}

void ioopm_hash_table_destroy(ioopm_hash_table_t *ht) {
  free(ht);
}

void ioopm_hash_table_insert(ioopm_hash_table_t *ht, int key, char *value) {
  // TODO: Stub
}

//char* istället ?? //TODO
void ioopm_hash_table_lookup(ioopm_hash_table_t *ht, int key) {
  // TODO: Stub
  return NULL;
}
/*int main(int argc, char *argv[])
{
  entry_t a = { .key = 1, .value = argv[1] };
  entry_t b = { .key = 2, .value = argv[2], .next = &a };
  entry_t c = { .key = 3, .value = argv[3], .next = &b };
  entry_t d = { .key = 4, .value = argv[4] };
  entry_t e = { .key = 5, .value = argv[5] };
  entry_t f = { .key = 6, .value = argv[6], .next = &e };
  ioopm_hash_table_t ht = { .buckets = { 0 } };
  ht.buckets[3] = &c;
  ht.buckets[8] = &d;
  ht.buckets[15] = &f;

  return 0;
}*/
