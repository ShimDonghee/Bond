 #pragma warning(disable: 4819)
#include <ql/quantlib.hpp>
#include <ql/qldefines.hpp>
#if !defined(BOOST_ALL_NO_LIB) && defined(BOOST_MSVC)
#  include <ql/auto_link.hpp>
#endif

#include <ql/termstructures/yield/bondhelpers.hpp>
#include <ql/time/calendars/target.hpp>
#include <ql/time/daycounters/actualactual.hpp>
#include <iostream>
#include <iomanip>

using namespace QuantLib;

int main() {

    // Set up the market data
    Calendar calendar = TARGET();
    Date settlementDate = Date(1, January, 2022);
    Settings::instance().evaluationDate() = settlementDate;
    DayCounter dayCounter = ActualActual(ActualActual::Bond);
    Real qq = 100.0;
    ext::shared_ptr<SimpleQuote> quote(new SimpleQuote(qq));
    Handle<Quote> price(quote);
    // Handle<Quote> price = Handle<Quote>(std::make_shared<SimpleQuote> (qq));
    Natural settlementDays = 2;
    Real faceAmount = 100.0;
    Schedule schedule = Schedule(Date(1, January, 2023), Date(1, January, 2028), Period(Semiannual), calendar, Unadjusted, Unadjusted, DateGeneration::Backward, false);
    std::vector<Rate> coupons;
    coupons.push_back(0.05);
    DayCounter couponDayCounter = ActualActual(ActualActual::ISDA);
    BusinessDayConvention paymentConvention = ModifiedFollowing;
    Real redemption = 100.0;

    FixedRateBondHelper bondHelper(price, settlementDays, faceAmount, schedule, coupons, couponDayCounter, paymentConvention, redemption);

    ext::shared_ptr<FixedRateBond> bond = bondHelper.fixedRateBond();

    // Print the bond's cash flows
    for (Size i = 0; i < bond->cashflows().size(); i++) {
        std::cout << bond->cashflows()[i]->date() << "\t" << bond->cashflows()[i]->amount() << std::endl;
    }

    return 0;
}
