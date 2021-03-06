#include "stdafx.h"


using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace CloseGL;
using namespace CloseGLTest::Toolkit;

namespace CloseGLTest
{
	TEST_CLASS(TestTriangleRasterizater)
	{
	public:

		TEST_METHOD(DrawColoredTriangle)
		{
			TestView tv(5000);

			Geometry::GeometryPipelineOutput go;
			go.Format.ElementCount = 4;
			go.Format.PositionElementCount = 2;
			go.Format.PositionElementOffset = 0;
			go.Format.UsedElementCount = 4;

			go.Outputs.push_back(Geometry::GeometryPipelineOutput::ThreadOut());
			auto& out = go.Outputs.back();

			//V0 P0
			out.StripData.push_back(false);
			out.VertexData.push_back(0);
			out.VertexData.push_back(0);
			out.VertexData.push_back(0);
			out.VertexData.push_back(0);

			//V1 P0
			out.StripData.push_back(true);
			out.VertexData.push_back(1);
			out.VertexData.push_back(1);
			out.VertexData.push_back(1);
			out.VertexData.push_back(1);

			//V2 P0
			out.StripData.push_back(true);
			out.VertexData.push_back(0.25);
			out.VertexData.push_back(0.75);
			out.VertexData.push_back(0);
			out.VertexData.push_back(1);


			auto raster = CloseGL::PixelPipeline::CreateTriangleRasterizater();

			PixelPipeline::PixelPipeline::Status status;
			status.PixelShader = [](const float* arg, const CloseGL::Geometry::GeometryDataFormat& fmt, std::vector<CloseGL::PixelFormats::ColorRGBA<float>>& out)
			{
				out.push_back({ arg[2],arg[3],1,0 });
			};

			tv.SetUpdateFunction([raster, &go, &status](float time, CloseGL::Surface<CloseGL::PixelFormats::ColorRGBA<float>>& sur) {
				sur.Clear(CloseGL::PixelFormats::ColorRGBA<float>{0, 0, 0, 1});

				CloseGL::PixelPipeline::FrameBuffer fb;
				fb.ColorBuffers.push_back(&sur);

				raster->Draw(go, fb, status);
			});
			tv.Run();
		}

		TEST_METHOD(DrawColoredQuad)
		{
			TestView tv(50000);

			Geometry::GeometryPipelineOutput go;
			go.Format.ElementCount = 4;
			go.Format.PositionElementCount = 2;
			go.Format.PositionElementOffset = 0;
			go.Format.UsedElementCount = 4;

			go.Outputs.push_back(Geometry::GeometryPipelineOutput::ThreadOut());
			auto& out = go.Outputs.back();

			//V0 P0
			out.StripData.push_back(false);
			out.VertexData.push_back(0);
			out.VertexData.push_back(0);
			out.VertexData.push_back(0);
			out.VertexData.push_back(0);

			//V1 P0
			out.StripData.push_back(true);
			out.VertexData.push_back(1);
			out.VertexData.push_back(1);
			out.VertexData.push_back(1);
			out.VertexData.push_back(1);

			//V2 P0
			out.StripData.push_back(true);
			out.VertexData.push_back(0.25f);
			out.VertexData.push_back(0.75f);
			out.VertexData.push_back(0);
			out.VertexData.push_back(1);

			//V2 P0
			out.StripData.push_back(true);
			out.VertexData.push_back(0.05f);
			out.VertexData.push_back(0.99f);
			out.VertexData.push_back(0);
			out.VertexData.push_back(1);


			auto raster = CloseGL::PixelPipeline::CreateTriangleRasterizater();

			PixelPipeline::PixelPipeline::Status status;
			status.PixelShader = [](const float* arg, const CloseGL::Geometry::GeometryDataFormat& fmt, std::vector<CloseGL::PixelFormats::ColorRGBA<float>>& out)
			{
				out.push_back({ arg[2],arg[3],1,0 });
			};

			tv.SetUpdateFunction([raster, &go, &status](float time, CloseGL::Surface<CloseGL::PixelFormats::ColorRGBA<float>>& sur) {
				sur.Clear(CloseGL::PixelFormats::ColorRGBA<float>{0, 0, 0, 1});

				CloseGL::PixelPipeline::FrameBuffer fb;
				fb.ColorBuffers.push_back(&sur);

				raster->Draw(go, fb, status);
			});
			tv.Run();
		}

	};

	

};

