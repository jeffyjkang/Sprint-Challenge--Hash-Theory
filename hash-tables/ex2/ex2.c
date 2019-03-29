#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hashtable.h"
#include "ex2.h"

char **reconstruct_trip(Ticket **tickets, int length)
{
  // create ht with 16 capacity
  HashTable *ht = create_hash_table(16);
  // allocate enough mem of pointer char type assigned to the array of routes
  char **route = malloc(length * sizeof(char *));

  // YOUR CODE HERE
  // loop through the length of tickets
  for (int i = 0; i < length; i++)
  {
    // for each index pass in the ticket source as the key and destination as value
    hash_table_insert(ht, tickets[i]->source, tickets[i]->destination);
  }
  // start route from 0th index or first location, pass in the ht and "NONE" as key
  route[0] = hash_table_retrieve(ht, "NONE");
  // loop through length of tickets again to add trips, start at 1
  for (int i = 1; i < length; i++)
  {
    // ith location in route can be found by checking ht for i-1
    route[i] = hash_table_retrieve(ht, route[i - 1]);
  }
  // return route
  return route;
}

void print_route(char **route, int length)
{
  for (int i = 0; i < length; i++)
  {
    printf("%s\n", route[i]);
  }
}

LinkedPair *create_pair(char *key, char *value)
{
  LinkedPair *pair = malloc(sizeof(LinkedPair));
  pair->key = key;
  pair->value = value;
  pair->next = NULL;

  return pair;
}

// djb2 hash function
unsigned int hash(char *str, int max)
{
  unsigned long hash = 5381;
  int c;
  unsigned char *u_str = (unsigned char *)str;

  while ((c = *u_str++))
  {
    hash = ((hash << 5) + hash) + c;
  }

  return hash % max;
}

void destroy_pair(LinkedPair *pair)
{
  if (pair != NULL)
    free(pair);
}

HashTable *create_hash_table(int capacity)
{
  HashTable *ht = malloc(sizeof(HashTable));
  ht->capacity = capacity;
  ht->storage = calloc(capacity, sizeof(LinkedPair *));

  return ht;
}

void hash_table_insert(HashTable *ht, char *key, char *value)
{
  unsigned int index = hash(key, ht->capacity);

  LinkedPair *current_pair = ht->storage[index];
  LinkedPair *last_pair;

  while (current_pair != NULL && strcmp(current_pair->key, key) != 0)
  {
    last_pair = current_pair;
    current_pair = last_pair->next;
  }

  if (current_pair != NULL)
  {
    current_pair->value = value;
  }
  else
  {
    LinkedPair *new_pair = create_pair(key, value);
    new_pair->next = ht->storage[index];
    ht->storage[index] = new_pair;
  }
}

void hash_table_remove(HashTable *ht, char *key)
{
  unsigned int index = hash(key, ht->capacity);

  LinkedPair *current_pair = ht->storage[index];
  LinkedPair *previous_pair = NULL;

  while (current_pair != NULL && strcmp(current_pair->key, key) != 0)
  {
    previous_pair = current_pair;
    current_pair = current_pair->next;
  }

  if (current_pair == NULL)
  {

    fprintf(stderr, "Unable to remove entry with key: %s\n", key);
  }
  else
  {

    if (previous_pair == NULL)
    { // Removing the first element in the Linked List
      ht->storage[index] = current_pair->next;
    }
    else
    {
      previous_pair->next = current_pair->next;
    }

    destroy_pair(current_pair);
  }
}

char *hash_table_retrieve(HashTable *ht, char *key)
{
  unsigned int index = hash(key, ht->capacity);

  LinkedPair *current_pair = ht->storage[index];

  while (current_pair != NULL)
  {
    if (strcmp(current_pair->key, key) == 0)
    {
      return current_pair->value;
    }
    current_pair = current_pair->next;
  }

  return NULL;
}

void destroy_hash_table(HashTable *ht)
{
  LinkedPair *current_pair;
  LinkedPair *pair_to_destroy;

  for (int i = 0; i < ht->capacity; i++)
  {
    current_pair = ht->storage[i];
    while (current_pair != NULL)
    {
      pair_to_destroy = current_pair;
      current_pair = current_pair->next;
      destroy_pair(pair_to_destroy);
    }
  }

  free(ht->storage);
  free(ht);
}

HashTable *hash_table_resize(HashTable *ht)
{
  HashTable *new_ht = create_hash_table(2 * ht->capacity);

  LinkedPair *current_pair;
  for (int i = 0; i < ht->capacity; i++)
  {
    current_pair = ht->storage[i];
    while (current_pair != NULL)
    {
      hash_table_insert(new_ht, current_pair->key, current_pair->value);
      current_pair = current_pair->next;
    }
  }
  destroy_hash_table(ht);

  return new_ht;
}

#ifndef TESTING
int main(void)
{
  // Short test
  Ticket **tickets = malloc(10 * sizeof(Ticket *));

  Ticket *ticket_1 = malloc(sizeof(Ticket));
  ticket_1->source = "PIT";
  ticket_1->destination = "ORD";
  tickets[0] = ticket_1;

  Ticket *ticket_2 = malloc(sizeof(Ticket));
  ticket_2->source = "XNA";
  ticket_2->destination = "CID";
  tickets[1] = ticket_2;

  Ticket *ticket_3 = malloc(sizeof(Ticket));
  ticket_3->source = "SFO";
  ticket_3->destination = "BHM";
  tickets[2] = ticket_3;

  Ticket *ticket_4 = malloc(sizeof(Ticket));
  ticket_4->source = "FLG";
  ticket_4->destination = "XNA";
  tickets[3] = ticket_4;

  Ticket *ticket_5 = malloc(sizeof(Ticket));
  ticket_5->source = "NONE";
  ticket_5->destination = "LAX";
  tickets[4] = ticket_5;

  Ticket *ticket_6 = malloc(sizeof(Ticket));
  ticket_6->source = "LAX";
  ticket_6->destination = "SFO";
  tickets[5] = ticket_6;

  Ticket *ticket_7 = malloc(sizeof(Ticket));
  ticket_7->source = "CID";
  ticket_7->destination = "SLC";
  tickets[6] = ticket_7;

  Ticket *ticket_8 = malloc(sizeof(Ticket));
  ticket_8->source = "ORD";
  ticket_8->destination = "NONE";
  tickets[7] = ticket_8;

  Ticket *ticket_9 = malloc(sizeof(Ticket));
  ticket_9->source = "SLC";
  ticket_9->destination = "PIT";
  tickets[8] = ticket_9;

  Ticket *ticket_10 = malloc(sizeof(Ticket));
  ticket_10->source = "BHM";
  ticket_10->destination = "FLG";
  tickets[9] = ticket_10;

  print_route(reconstruct_trip(tickets, 10), 10); // PDX, DCA, NONE

  return 0;
}
#endif
