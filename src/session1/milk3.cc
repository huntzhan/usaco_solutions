/*
ID: program41
LANG: C++11
TASK: milk3
*/
#include <ostream>
#include <fstream>
#include <string>
#include <set>
#include <unordered_set>
#include <vector>
#include <iterator>

using std::ifstream;
using std::ofstream;
using std::endl;
using std::string;
using std::to_string;
using std::set;
using std::unordered_set;
using std::vector;
using std::distance;

const string kTask = "milk3";
const string kInputFile = kTask + ".in";
const string kOutputFile = kTask + ".out";

// debug.
#include <iostream>
using std::cout;

class Bucket {
 public:
  Bucket(const int &capacity, const int &value)
      : capacity_(capacity), value_(value) {/* empty */}

  void PourFrom(Bucket *other_bucket) {
    int difference = capacity_ - value_;
    if (other_bucket->value_ < difference) {
      difference = other_bucket->value_;
    }
    // pour from other_bucket to this bucket.
    value_ += difference;
    other_bucket->value_ -= difference;
  }

  string ToString() const {
    return to_string(value_);
  }

  bool IsFull() const {
    return value_ == capacity_;
  }
  
  bool IsEmpty() const {
    return value_ == 0;
  }

  const int capacity_;
  int value_;
};

class MilkAllocation {
 public:
  MilkAllocation(const int &a, const int &b, const int &c)
      : bucket_a_(a, 0), bucket_b_(b, 0), bucket_c_(c, c)
      {/* empty */}
  MilkAllocation(const Bucket &a, const Bucket &b, const Bucket &c)
      : bucket_a_(a), bucket_b_(b), bucket_c_(c)
      {/* empty */}

  string Hash() const {
    const string value =
        bucket_a_.ToString()
        + "|" + bucket_b_.ToString()
        + "|" + bucket_c_.ToString();
    return value;
  }

  Bucket bucket_a_, bucket_b_, bucket_c_;
};

void SearchMilkAllocation(
    unordered_set<string> *searched_allocation_ptr,
    set<int> *values_of_bucket_c_ptr,
    const MilkAllocation &milk_allocation) {

  // pointer to data member.
  using PtrToBucketDataMember = Bucket MilkAllocation::*;
  const vector<PtrToBucketDataMember> ptr_to_bucket_members = {
      &MilkAllocation::bucket_a_,
      &MilkAllocation::bucket_b_,
      &MilkAllocation::bucket_c_};

  vector<PtrToBucketDataMember> buckets_not_full;
  vector<PtrToBucketDataMember> buckets_not_empty;

  for (auto ptr_to_bucket_member : ptr_to_bucket_members) {
    // get bucket.
    const auto &bucket = milk_allocation.*ptr_to_bucket_member;

    if (!bucket.IsFull()) {
      buckets_not_full.push_back(ptr_to_bucket_member);
    }
    if (!bucket.IsEmpty()) {
      buckets_not_empty.push_back(ptr_to_bucket_member);
    }
  }
  // search.
  for (auto not_empty : buckets_not_empty) {
    for (auto not_full : buckets_not_full) {
      // gennerate new allocation from old one.
      MilkAllocation new_allocation(
          milk_allocation.bucket_a_,
          milk_allocation.bucket_b_,
          milk_allocation.bucket_c_);

      if (not_empty == not_full) {
        continue;
      }

      Bucket &not_empty_bucket = new_allocation.*not_empty;
      Bucket &not_full_bucket = new_allocation.*not_full;
      not_full_bucket.PourFrom(&not_empty_bucket);

      const string hash_value = new_allocation.Hash();
      // check searched or not.
      if (searched_allocation_ptr->find(hash_value)
          != searched_allocation_ptr->end()) {
        // if searched, just omit it.
        continue;
      }

      // check if bucket A is empty.
      if (new_allocation.bucket_a_.IsEmpty()) {
        values_of_bucket_c_ptr->insert(
            new_allocation.bucket_c_.value_);
      }

      // mark searched.
      searched_allocation_ptr->insert(hash_value);
      // keep searching.
      SearchMilkAllocation(
          searched_allocation_ptr,
          values_of_bucket_c_ptr,
          new_allocation);
    }
  }
}

int main() {
  ifstream fin(kInputFile);
  ofstream fout(kOutputFile);

  int capacity_a, capacity_b, capacity_c;
  fin >> capacity_a >> capacity_b >> capacity_c;

  const MilkAllocation milk_allocation(
      capacity_a, capacity_b, capacity_c);

  unordered_set<string> searched_allocation;
  set<int> values_of_bucket_c;
  SearchMilkAllocation(
      &searched_allocation,
      &values_of_bucket_c,
      milk_allocation);

  // output.
  for (auto iter = values_of_bucket_c.cbegin();
       iter != values_of_bucket_c.cend(); ++iter) {
    fout << *iter;
    const int &printed = distance(
        values_of_bucket_c.cbegin(), iter);
    if (printed != values_of_bucket_c.size() - 1) {
      fout << " ";
    }
  }
  fout << endl;
}
