#include <gtest/gtest.h>

#include "../Model/model.h"

namespace s21 {

TEST(Viewer, Cube) {
  Model* pointer = Model::get_model();
  pointer->set_model("file_obj/Cube.obj");
  EXPECT_EQ(24, pointer->get_points().size());
  EXPECT_EQ(72, pointer->get_connections().size());

  pointer->affine_rotate(0, 90);
  EXPECT_EQ((pointer->get_points()[0] + 0.405000) < 1E-06, true);
  EXPECT_DOUBLE_EQ((pointer->get_points()[1] - 0.404677) < 1E-6, true);
  EXPECT_DOUBLE_EQ((pointer->get_points()[2] - 0.405322) < 1E-6, true);

  pointer->affine_shift(1, 10);
  EXPECT_DOUBLE_EQ((pointer->get_points()[0] + 0.405000) < 1E-6, true);
  EXPECT_DOUBLE_EQ((pointer->get_points()[1] - 10.404677) < 1E-6, true);
  EXPECT_DOUBLE_EQ((pointer->get_points()[2] - 0.405322) < 1E-6, true);

  pointer->affine_scale(0.1);
  EXPECT_DOUBLE_EQ((pointer->get_points()[0] + 0.040500) < 1E-6, true);
  EXPECT_DOUBLE_EQ((pointer->get_points()[1] - 1.040468) < 1E-6, true);
  EXPECT_DOUBLE_EQ((pointer->get_points()[2] - 0.040532) < 1E-6, true);

  pointer->set_model("file_obj/1.obj");
  EXPECT_EQ(0, pointer->get_points().size());
  EXPECT_EQ(0, pointer->get_connections().size());

  pointer->set_model("file_obj/Cow.obj");
  EXPECT_EQ(8709, pointer->get_points().size());
  EXPECT_EQ(34824, pointer->get_connections().size());
}

}  // namespace s21