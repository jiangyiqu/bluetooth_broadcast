import esphome.codegen as cg
import esphome.config_validation as cv
from esphome.components import sensor
from esphome.const import CONF_ID

# 创建组件命名空间
bluetooth_broadcast_ns = cg.esphome_ns.namespace("bluetooth_broadcast")
BluetoothBroadcast = bluetooth_broadcast_ns.class_("BluetoothBroadcast", cg.Component)

# 配置项常量
CONF_SEND_COUNT = "send_count"
CONF_INTERVAL = "interval"
CONF_MANUFACTURER_DATA = "manufacturer_data"
CONF_BROADCASTING = "broadcasting"

# 配置项验证
CONFIG_SCHEMA = cv.Schema({
    cv.GenerateID(): cv.declare_id(BluetoothBroadcast),
    CONF_SEND_COUNT: cv.int_,
    CONF_INTERVAL: cv.positive_int,
    CONF_MANUFACTURER_DATA: cv.optional(cv.string),
    CONF_BROADCASTING: cv.boolean,
}).extend(cg.COMPONENT_SCHEMA)

# 从 YAML 配置文件创建组件
def to_code(config):
    var = cg.new_Pvariable(config[CONF_ID])

    cg.add(var.set_send_count(config[CONF_SEND_COUNT]))
    cg.add(var.set_interval(config[CONF_INTERVAL]))
    if CONF_MANUFACTURER_DATA in config:
        cg.add(var.set_manufacturer_data(config[CONF_MANUFACTURER_DATA]))
    if config[CONF_BROADCASTING]:
        cg.add(var.start_broadcasting())
    else:
        cg.add(var.stop_broadcasting())

    return var
