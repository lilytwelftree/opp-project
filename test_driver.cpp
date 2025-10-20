#include <cassert>
#include <iostream>
#include <string>
#include <vector>

#include "Cake.h"
#include "Customer.h"
#include "Filling.h"
#include "Frosting.h"
#include "Order.h"
#include "Sprinkles.h"
#include "Store.h"
#include "Time.h"
#include "Topping.h"

using namespace std;

class TestDriver {
 private:
  int testsPassed = 0;
  int testsFailed = 0;

  void logTest(string testName, bool passed, string details = "") {
    if (passed) {
      cout << "PASS: " << testName << endl;
      testsPassed++;
    } else {
      cout << "FAIL: " << testName;
      if (!details.empty()) cout << " - " << details;
      cout << endl;
      testsFailed++;
    }
  }

  void logSection(string sectionName) {
    cout << "\n" << string(50, '=') << endl;
    cout << "testing: " << sectionName << endl;
    cout << string(50, '=') << endl;
  }

 public:
  // test submitcake functionality
  void testSubmitCake() {
    logSection("submitcake functionality");

    // we dont have a game class yet, so we're simulating submitcake behavior
    // by testing cake creation and storage

    // testing valid complete cake (choc sprinkles, strawberry filling, vanilla
    // frosting)
    Cake cake1;
    cake1.SetFlavour("Vanilla");

    Filling filling1("Strawberry");
    filling1.SetDecorationChoice("Strawberry");
    cake1.AddDecoration(&filling1);

    Frosting frosting1("Vanilla");
    frosting1.SetDecorationChoice("Vanilla");
    cake1.AddDecoration(&frosting1);

    Sprinkles sprinkles1("Chocolate");
    sprinkles1.SetDecorationChoice("Chocolate");
    cake1.AddDecoration(&sprinkles1);

    bool test1 = !cake1.GetFlavour().empty() && !cake1.GetFilling().empty() &&
                 !cake1.GetTopping().empty();
    logTest(
        "valid complete cake (chocolate sprinkles, strawberry filling, vanilla "
        "frosting)",
        test1, test1 ? "" : "cake components not set properly");

    // testing complete cake (pink sprinkles, jam filling, vanilla frosting)
    Cake cake2;
    cake2.SetFlavour("Chocolate");

    Filling filling2("Jam");
    filling2.SetDecorationChoice("Jam");
    cake2.AddDecoration(&filling2);

    Frosting frosting2("Vanilla");
    frosting2.SetDecorationChoice("Vanilla");
    cake2.AddDecoration(&frosting2);

    Sprinkles sprinkles2("Pink");
    sprinkles2.SetDecorationChoice("Pink");
    cake2.AddDecoration(&sprinkles2);

    bool test2 = !cake2.GetFlavour().empty() && !cake2.GetFilling().empty() &&
                 !cake2.GetTopping().empty();
    logTest(
        "valid complete cake (pink sprinkles, jam filling, vanilla frosting)",
        test2, test2 ? "" : "cake components not set properly");

    // testing incomplete input (sprinkles, chocolate frosting, no filling)
    Cake cake3;
    cake3.SetFlavour("Chocolate");

    Frosting frosting3("Chocolate");
    frosting3.SetDecorationChoice("Chocolate");
    cake3.AddDecoration(&frosting3);

    Sprinkles sprinkles3("Rainbow");
    sprinkles3.SetDecorationChoice("Rainbow");
    cake3.AddDecoration(&sprinkles3);

    bool test3 = !cake3.GetFlavour().empty() && !cake3.GetTopping().empty() &&
                 cake3.GetFilling().empty();  // no filling
    logTest("incomplete input (sprinkles, chocolate frosting)", test3,
            test3 ? "" : "incomplete cake not handled properly");

    // testing empty cake (no flavour, empty decorations)
    Cake cake4;
    bool test4 = cake4.GetFlavour() == "None" && cake4.GetFilling().empty() &&
                 cake4.GetTopping().empty();
    logTest("empty cake (no flavour, empty decorations)", test4,
            test4 ? "" : "empty cake not handled properly");
  }

  // test settime functionality
  void testSetTime() {
    logSection("settime functionality");

    // test case 1: valid input level 1
    Time time1;
    time1.SetTimeLimitByLevel(1);
    bool test1 = time1.GetLimitSeconds() == 180;
    logTest("valid input level 1", test1,
            test1 ? ""
                  : "expected 180 seconds, got " +
                        to_string(time1.GetLimitSeconds()));

    // test case 2: valid input level 3
    Time time2;
    time2.SetTimeLimitByLevel(3);
    bool test2 = time2.GetLimitSeconds() == 150;  // 180 - (3-1)*15 = 150
    logTest("valid input level 3", test2,
            test2 ? ""
                  : "expected 150 seconds, got " +
                        to_string(time2.GetLimitSeconds()));

    // test case 3: invalid level 0
    Time time3;
    time3.SetTimeLimitByLevel(0);
    bool test3 = time3.GetLimitSeconds() == 180;  // should default to 180
    logTest("invalid level 0", test3,
            test3 ? ""
                  : "expected 180 seconds (default), got " +
                        to_string(time3.GetLimitSeconds()));

    // test case 4: invalid level -2
    Time time4;
    time4.SetTimeLimitByLevel(-2);
    bool test4 = time4.GetLimitSeconds() == 180;  // should default to 180
    logTest("invalid level -2", test4,
            test4 ? ""
                  : "expected 180 seconds (default), got " +
                        to_string(time4.GetLimitSeconds()));

    // test case 5: invalid level 12 (should cap at minimum)
    Time time5;
    time5.SetTimeLimitByLevel(12);
    bool test5 = time5.GetLimitSeconds() >= 40;  // should not go below 40
    logTest("invalid level 12", test5,
            test5 ? ""
                  : "expected >= 40 seconds, got " +
                        to_string(time5.GetLimitSeconds()));
  }

  // test updatelevel functionality
  void testUpdateLevel() {
    logSection("updatelevel functionality");

    // note: since we dont have store class fully implemented, we'll test what
    // we can

    Store store;

    // test case 1: valid input (revenue: $100, required customer satisfaction:
    // 4)
    store.UpdateRevenue(100.0);
    store.UpdateRating(4);
    // note: we cant fully test upgradestore() without the complete
    // implementation
    bool test1 = store.GetRevenue() == 100.0 && store.GetRating() == 4;
    logTest("valid input (revenue: $100, rating: 4)", test1,
            test1 ? "" : "revenue or rating not set correctly");

    // test case 2: valid input (revenue: $99, required customer satisfaction:
    // 4)
    store.UpdateRevenue(99.0);
    store.UpdateRating(4);
    bool test2 = store.GetRevenue() == 99.0 && store.GetRating() == 4;
    logTest("valid input (revenue: $99, rating: 4)", test2,
            test2 ? "" : "revenue or rating not set correctly");

    // test case 3: invalid input (revenue: $-10, required customer
    // satisfaction: 3)
    store.UpdateRevenue(-10.0);
    store.UpdateRating(3);
    bool test3 = store.GetRevenue() == -10.0;  // currently accepts negative
    logTest("invalid input (revenue: $-10, rating: 3)", test3,
            test3 ? "negative revenue accepted (potential bug)"
                  : "revenue not set correctly");

    // test case 4: valid input (revenue: $0, required customer satisfaction: 0)
    store.UpdateRevenue(0.0);
    store.UpdateRating(0);
    bool test4 = store.GetRevenue() == 0.0 && store.GetRating() == 0;
    logTest("valid input (revenue: $0, rating: 0)", test4,
            test4 ? "" : "zero values not handled correctly");
  }

  // test applydecoration functionality
  void testApplyDecoration() {
    logSection("applydecoration functionality");

    // test case 1: valid input (filling class, fillingchoice: "strawberry jam")
    Filling filling1("Strawberry Jam");
    filling1.SetDecorationChoice("Strawberry Jam");
    filling1.ApplyDecoration();

    Cake cake1;
    cake1.AddDecoration(&filling1);

    bool test1 = cake1.GetFilling() == "Strawberry Jam";
    logTest("valid input (filling: strawberry jam)", test1,
            test1 ? "" : "filling not applied correctly");

    // test case 2: valid input (frosting class, toppingchoice: "pink
    // buttercream")
    Frosting frosting1("Pink Buttercream");
    frosting1.SetDecorationChoice("Pink Buttercream");
    frosting1.ApplyDecoration();

    Cake cake2;
    cake2.AddDecoration(&frosting1);

    bool test2 = !cake2.GetTopping().empty();
    logTest("valid input (frosting: pink buttercream)", test2,
            test2 ? "" : "frosting not applied correctly");

    // test case 3: invalid input (frosting class, empty string)
    Frosting frosting2("");
    frosting2.SetDecorationChoice("");
    frosting2.ApplyDecoration();

    Cake cake3;
    cake3.AddDecoration(&frosting2);

    bool test3 = cake3.GetTopping().empty() || cake3.GetTopping() == "None";
    logTest("invalid input (frosting: empty string)", test3,
            test3 ? "" : "empty frosting should not be applied");
  }

  // test sprinkles class
  void testSprinkles() {
    logSection("sprinkles class testing");

    // test case 1: valid input - "rainbow" sprinkles
    Sprinkles sprinkles1("Rainbow");
    sprinkles1.SetDecorationChoice("Rainbow");
    sprinkles1.ApplyDecoration();

    Cake cake1;
    cake1.AddDecoration(&sprinkles1);

    bool test1 = !cake1.GetTopping().empty();
    logTest("valid input (sprinkles: rainbow)", test1,
            test1 ? "" : "sprinkles not visible; order incomplete");

    // test case 2: valid input - "none" sprinkles
    Sprinkles sprinkles2("None");
    sprinkles2.SetDecorationChoice("None");
    sprinkles2.ApplyDecoration();

    Cake cake2;
    cake2.AddDecoration(&sprinkles2);

    bool test2 = cake2.GetTopping() == "None" || cake2.GetTopping().empty();
    logTest(
        "valid input (sprinkles: none)", test2,
        test2 ? "" : "cannot skip sprinkles when desired; forces selection");

    // test polymorphism
    Decorations* dec1 = new Sprinkles("Chocolate");
    dec1->SetDecorationChoice("Chocolate");
    dec1->ApplyDecoration();

    Cake cake3;
    cake3.AddDecoration(dec1);

    bool test3 = !cake3.GetTopping().empty();
    logTest("polymorphism test (sprinkles through decorations*)", test3,
            test3 ? "" : "polymorphism not working correctly");

    delete dec1;
  }

  // test givereview functionality
  void testGiveReview() {
    logSection("givereview functionality");

    Customer customer(1);

    // test case 1: perfect accuracy, time remaining
    int stars1 = customer.GiveReview(4, 4, 60);  // 4/4 correct, 60 seconds left
    bool test1 = stars1 == 5;
    logTest("perfect accuracy, time remaining (4/4 correct, 60s left)", test1,
            test1 ? "" : "expected 5 stars, got " + to_string(stars1));

    // test case 2: perfect accuracy, zero time remaining
    int stars2 = customer.GiveReview(4, 4, 0);  // 4/4 correct, 0 seconds left
    bool test2 =
        stars2 >= 3 && stars2 <= 4;  // should be high but penalized for time
    logTest("perfect accuracy, zero time remaining (4/4 correct, 0s left)",
            test2, test2 ? "" : "expected 3-4 stars, got " + to_string(stars2));

    // test case 3: low accuracy, good time remaining
    int stars3 =
        customer.GiveReview(1, 4, 120);       // 1/4 correct, 120 seconds left
    bool test3 = stars3 >= 1 && stars3 <= 3;  // should be low due to accuracy
    logTest("low accuracy, good time remaining (1/4 correct, 120s left)", test3,
            test3 ? "" : "expected 1-3 stars, got " + to_string(stars3));

    // test case 4: low accuracy, time penalty
    int stars4 = customer.GiveReview(2, 4, 30);  // 2/4 correct, 30 seconds left
    bool test4 =
        stars4 >= 1 && stars4 <= 3;  // should be low due to both factors
    logTest("low accuracy, time penalty (2/4 correct, 30s left)", test4,
            test4 ? "" : "expected 1-3 stars, got " + to_string(stars4));

    // test case 5: invalid input - negative time
    int stars5 = customer.GiveReview(4, 4, -10);  // 4/4 correct, -10 seconds
    bool test5 = stars5 >= 1 && stars5 <= 5;      // should handle gracefully
    logTest(
        "invalid input - negative time (4/4 correct, -10s)", test5,
        test5 ? ""
              : "negative time not handled properly, got " + to_string(stars5));

    // test case 6: division by zero protection
    int stars6 = customer.GiveReview(0, 0, 60);  // 0/0 correct
    bool test6 = stars6 == 1;  // should return 1 to prevent division by zero
    logTest("division by zero protection (0/0 correct)", test6,
            test6 ? ""
                  : "expected 1 star (division by zero protection), got " +
                        to_string(stars6));
  }

  // test edge cases and integration
  void testEdgeCases() {
    logSection("edge cases and integration");

    // test 100 cake submissions (vector capacity)
    vector<Cake> customCakes;
    for (int i = 0; i < 100; i++) {
      Cake cake;
      cake.SetFlavour("Test" + to_string(i));
      customCakes.push_back(cake);
    }

    bool test1 = customCakes.size() == 100;
    logTest("100 cake submissions (vector capacity)", test1,
            test1 ? "" : "vector capacity issue");

    // test time display functionality
    Time time;
    time.SetTimeLimitByLevel(2);
    time.DisplayTime();
    bool test2 = time.GetLimitSeconds() == 165;
    logTest("time display functionality", test2,
            test2 ? "" : "time display not working correctly");

    // test customer-time integration
    Customer customer(1);
    Time customerTime = customer.GetTimeLimit();
    customerTime.SetTimeLimitByLevel(3);
    bool test3 = customerTime.GetLimitSeconds() == 150;
    logTest("customer-time integration", test3,
            test3 ? "" : "customer-time integration not working");
  }

  void runAllTests() {
    cout << "comprehensive test suite for cake shop simulation" << endl;
    cout << string(60, '=') << endl;

    testSubmitCake();
    testSetTime();
    testUpdateLevel();
    testApplyDecoration();
    testSprinkles();
    testGiveReview();
    testEdgeCases();

    // Summary
    cout << "\n" << string(60, '=') << endl;
    cout << "test summary" << endl;
    cout << string(60, '=') << endl;
    cout << "Tests Passed: " << testsPassed << endl;
    cout << "Tests Failed: " << testsFailed << endl;
    cout << "Total Tests: " << (testsPassed + testsFailed) << endl;
    cout << "Success Rate: "
         << (testsPassed * 100 / (testsPassed + testsFailed)) << "%" << endl;

    if (testsFailed == 0) {
      cout << "\nALL TESTS PASSED! Your classes are working correctly!" << endl;
    } else {
      cout << "\nSome tests failed. Check the details above for issues to fix."
           << endl;
    }
  }
};

int main() {
  TestDriver driver;
  driver.runAllTests();
  return 0;
}
