#pragma once
#include "../../node.h"
#include <runtime/k210/k210_sim_types.h>
#include <xtensor/xtensor.hpp>

namespace nncase
{
namespace ir
{
    namespace k210
    {
        class fake_kpu_conv2d : public node
        {
        public:
            DEFINE_NODE_OPCODE(op_k210_fake_kpu_conv2d);

            input_connector &input() { return input_at(0); }
            output_connector &output() { return output_at(0); }

            bool is_depthwise() const noexcept { return is_depthwise_; }
            int32_t input_channels() const noexcept { return is_depthwise() ? (int32_t)weights_.shape()[0] : (int32_t)weights_.shape()[1]; }
            int32_t output_channels() const noexcept { return (int32_t)weights_.shape()[0]; }
            runtime::k210::kpu_filter_type_t filter_type() const noexcept { return filter_type_; }
            runtime::k210::kpu_pool_type_t pool_type() const noexcept { return pool_type_; }
            const xt::xtensor<float, 4> &weights() const noexcept { return weights_; }
            const xt::xtensor<float, 1> &bias() const noexcept { return bias_; }
            value_range<float> fused_activation() const noexcept { return fused_activation_; }

            fake_kpu_conv2d(shape_t input_shape, bool is_depthwise, runtime::k210::kpu_filter_type_t filter_type, runtime::k210::kpu_pool_type_t pool_type, xt::xtensor<float, 4> weights, xt::xtensor<float, 1> bias, value_range<float> fused_activation);

        private:
            xt::xtensor<float, 4> weights_;
            xt::xtensor<float, 1> bias_;
            bool is_depthwise_;
            runtime::k210::kpu_filter_type_t filter_type_;
            runtime::k210::kpu_pool_type_t pool_type_;
            value_range<float> fused_activation_;
        };
    }
}
}
