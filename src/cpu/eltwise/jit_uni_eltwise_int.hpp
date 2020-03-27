/*******************************************************************************
* Copyright 2020 Intel Corporation
*
* Licensed under the Apache License, Version 2.0 (the "License");
* you may not use this file except in compliance with the License.
* You may obtain a copy of the License at
*
*     http://www.apache.org/licenses/LICENSE-2.0
*
* Unless required by applicable law or agreed to in writing, software
* distributed under the License is distributed on an "AS IS" BASIS,
* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
* See the License for the specific language governing permissions and
* limitations under the License.
*******************************************************************************/

#ifndef CPU_JIT_UNI_ELTWISE_INT_HPP
#define CPU_JIT_UNI_ELTWISE_INT_HPP

#include <assert.h>

#include "c_types_map.hpp"
#include "primitive.hpp"
#include "type_helpers.hpp"
#include "utils.hpp"

#include "cpu_eltwise_pd.hpp"

#include "cpu_isa_traits.hpp"

namespace dnnl {
namespace impl {
namespace cpu {

struct jit_uni_eltwise_int_kernel;

template <cpu_isa_t isa, impl::data_type_t d_type>
struct jit_uni_eltwise_int_fwd_t : public primitive_t {
    struct pd_t : public cpu_eltwise_fwd_pd_t {
        using cpu_eltwise_fwd_pd_t::cpu_eltwise_fwd_pd_t;

        DECLARE_COMMON_PD_T(JIT_IMPL_NAME_HELPER("jit_int8:", isa, ""),
                jit_uni_eltwise_int_fwd_t);

        status_t init(engine_t *engine);
    };

    jit_uni_eltwise_int_fwd_t(const pd_t *apd);
    ~jit_uni_eltwise_int_fwd_t();

    typedef typename prec_traits<d_type>::type data_t;

    virtual status_t execute(const exec_ctx_t &ctx) const override {
        execute_forward(ctx);
        return status::success;
    }

private:
    void execute_forward(const exec_ctx_t &ctx) const;
    const pd_t *pd() const { return (const pd_t *)primitive_t::pd().get(); }
    jit_uni_eltwise_int_kernel *kernel_ = nullptr;
};

} // namespace cpu
} // namespace impl
} // namespace dnnl

#endif