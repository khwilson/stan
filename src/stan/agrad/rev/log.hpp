#ifndef __STAN__AGRAD__REV__LOG_HPP__
#define __STAN__AGRAD__REV__LOG_HPP__

#include <cmath>
#include <stan/agrad/rev/var.hpp>
#include <stan/agrad/rev/op/v_vari.hpp>
#include <limits>
#include <stan/math/error_handling/check_finite.hpp>
#include <stan/math/error_handling/check_greater.hpp>

namespace stan {
  namespace agrad {

    namespace {
      class log_vari : public op_v_vari {
      public:
        log_vari(vari* avi) :
          op_v_vari(std::log(avi->val_),avi) {
        }
        void chain() {
          avi_->adj_ += adj_ / avi_->val_;
        }
      };
    }

    /**
     * Return the natural log of the specified variable (cmath).
     *
     * The derivative is defined by
     *
     * \f$\frac{d}{dx} \log x = \frac{1}{x}\f$.
     *
     * @param a Variable whose log is taken.
     * @return Natural log of variable.
     */
    inline var log(const var& a) {
      static const char* function = "stan::agrad::log(%1%)";
      if (!stan::math::check_finite(function,a.val(),"value") || !stan::math::check_greater(function,a.val(),0.0,"value"))
        return std::numeric_limits<double>::quiet_NaN();
      return var(new log_vari(a.vi_));
    }
    
  }
}
#endif
