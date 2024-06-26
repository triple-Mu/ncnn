// Tencent is pleased to support the open source community by making ncnn available.
//
// Copyright (C) 2021 THL A29 Limited, a Tencent company. All rights reserved.
//
// Licensed under the BSD 3-Clause License (the "License"); you may not use this file except
// in compliance with the License. You may obtain a copy of the License at
//
// https://opensource.org/licenses/BSD-3-Clause
//
// Unless required by applicable law or agreed to in writing, software distributed
// under the License is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
// CONDITIONS OF ANY KIND, either express or implied. See the License for the
// specific language governing permissions and limitations under the License.

#include "pass_level2.h"

namespace pnnx {

class torch_mean : public GraphRewriterPass
{
public:
    const char* match_pattern_graph() const
    {
        return R"PNNXIR(7767517
6 5
pnnx.Input              input_0     0 1 input
pnnx.Input              input_1     0 1 dim
prim::Constant          op_0        0 1 keepdim value=%keepdim
prim::Constant          op_1        0 1 dtype value=*
aten::mean              op_2        4 1 input dim keepdim dtype out
pnnx.Output             output      1 0 out
)PNNXIR";
    }

    const char* type_str() const
    {
        return "torch.mean";
    }
};

REGISTER_GLOBAL_PNNX_GRAPH_REWRITER_PASS(torch_mean, 20)

class torch_mean_01 : public GraphRewriterPass
{
public:
    const char* match_pattern_graph() const
    {
        return R"PNNXIR(7767517
4 3
pnnx.Input              input_0     0 1 input
pnnx.Input              input_1     0 1 dim
aten::mean_dim          op_0        2 1 input dim out keepdim=%keepdim
pnnx.Output             output      1 0 out
)PNNXIR";
    }

    const char* type_str() const
    {
        return "torch.mean";
    }

    void write(Operator* op, const std::map<std::string, Parameter>& captured_params) const
    {
        bool keepdim;
        if (captured_params.at("keepdim").type == 2)
        {
            keepdim = captured_params.at("keepdim").i ? true : false;
        }
        else // if (captured_params.at("keepdim").type == 1)
        {
            keepdim = captured_params.at("keepdim").b;
        }

        op->params["keepdim"] = keepdim;
    }
};

REGISTER_GLOBAL_PNNX_GRAPH_REWRITER_PASS(torch_mean_01, 20)

class torch_mean_1 : public GraphRewriterPass
{
public:
    const char* match_pattern_graph() const
    {
        return R"PNNXIR(7767517
4 3
pnnx.Input              input_0     0 1 input
prim::Constant          op_0        0 1 dtype value=*
aten::mean              op_1        2 1 input dtype out
pnnx.Output             output      1 0 out
)PNNXIR";
    }

    const char* type_str() const
    {
        return "torch.mean";
    }
};

REGISTER_GLOBAL_PNNX_GRAPH_REWRITER_PASS(torch_mean_1, 20)

class torch_mean_onnx : public GraphRewriterPass
{
public:
    const char* match_pattern_graph() const
    {
        return R"PNNXIR(7767517
3 2
pnnx.Input              input       0 1 input
ReduceMean              op_0        1 1 input out axes=%axes keepdims=%keepdims
pnnx.Output             output      1 0 out
)PNNXIR";
    }

    const char* type_str() const
    {
        return "torch.mean";
    }

    void write(Operator* op, const std::map<std::string, Parameter>& captured_params) const
    {
        op->params["dim"] = captured_params.at("axes");
        op->params["keepdim"] = captured_params.at("keepdims").i ? true : false;
    }
};

REGISTER_GLOBAL_PNNX_GRAPH_REWRITER_PASS(torch_mean_onnx, 20)

class torch_mean_onnx_1 : public GraphRewriterPass
{
public:
    const char* match_pattern_graph() const
    {
        return R"PNNXIR(7767517
3 2
pnnx.Input              input       0 1 input
ReduceMean              op_0        1 1 input out axes=%axes
pnnx.Output             output      1 0 out
)PNNXIR";
    }

    const char* type_str() const
    {
        return "torch.mean";
    }

    void write(Operator* op, const std::map<std::string, Parameter>& captured_params) const
    {
        op->params["dim"] = captured_params.at("axes");
        op->params["keepdim"] = true;
    }
};

REGISTER_GLOBAL_PNNX_GRAPH_REWRITER_PASS(torch_mean_onnx_1, 20)

class torch_mean_onnx_2 : public GraphRewriterPass
{
public:
    const char* match_pattern_graph() const
    {
        return R"PNNXIR(7767517
4 3
pnnx.Input              input_0     0 1 input
pnnx.Input              input_1     0 1 dim
ReduceMean              op_0        2 1 input dim out keepdims=%keepdims noop_with_empty_axes=0
pnnx.Output             output      1 0 out
)PNNXIR";
    }

    const char* type_str() const
    {
        return "torch.mean";
    }

    void write(Operator* op, const std::map<std::string, Parameter>& captured_params) const
    {
        op->params["keepdim"] = captured_params.at("keepdims").i ? true : false;
    }
};

REGISTER_GLOBAL_PNNX_GRAPH_REWRITER_PASS(torch_mean_onnx_2, 20)

class torch_mean_onnx_3 : public GraphRewriterPass
{
public:
    const char* match_pattern_graph() const
    {
        return R"PNNXIR(7767517
3 2
pnnx.Input              input       0 1 input
ReduceMean              op_0        1 1 input out axes=%axes keepdims=%keepdims noop_with_empty_axes=0
pnnx.Output             output      1 0 out
)PNNXIR";
    }

    const char* type_str() const
    {
        return "torch.mean";
    }

    void write(Operator* op, const std::map<std::string, Parameter>& captured_params) const
    {
        op->params["dim"] = captured_params.at("axes");
        op->params["keepdim"] = captured_params.at("keepdims").i ? true : false;
    }
};

REGISTER_GLOBAL_PNNX_GRAPH_REWRITER_PASS(torch_mean_onnx_3, 20)

} // namespace pnnx
